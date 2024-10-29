#include "editor.h"
#include <yaml-cpp/yaml.h>
#include <fstream>

void Editor::draw_tiles() {
    for (auto& [coord, tile] : tiles.tiles_map) {
        uint16_t x = tiles_grid.x + (coord.first * TILE_SIZE);
        uint16_t y = tiles_grid.y + (coord.second * TILE_SIZE);
        std::shared_ptr texture = current_tileset->textures[tile];

        renderer.Copy(*texture,
                    Rect(0, 0, current_tileset->areas[tile].w, current_tileset->areas[tile].h),
                    Rect(x, y, texture->GetWidth() * 2, texture->GetHeight() * 2));
    }
}

void Editor::draw_textures() {
    int totalWidth = (1920 - 128);
    int textureX = 64;
    int textureY = (1080 * 2) / 3;

    for (auto& [key, texture] : current_tileset->textures) {
        SDL_Color textColor = (key == selected_texture) ? SDL_Color{100, 100, 255, 255} : SDL_Color{255, 255, 255, 255};
        Texture textTexture(renderer, font.RenderText_Blended(key, textColor));
        int textPosX = textureX + ((texture->GetWidth() * 4) / 2) - (textTexture.GetWidth() / 2);
        renderer.Copy(textTexture, NullOpt, 
                      Rect(textPosX, textureY - textTexture.GetHeight(), 
                        textTexture.GetWidth(), 
                        textTexture.GetHeight()
                     )
                    );
        
        renderer.Copy(*texture,
                    Rect(0, 0, current_tileset->areas[key].w, current_tileset->areas[key].h),
                    Rect(textureX, textureY, texture->GetWidth() * 4, texture->GetHeight() * 4));
        textureX += totalWidth / current_tileset->textures.size();
    }
}

void Editor::handle_event(const SDL_Event& event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        SDL_Point mousePos = { event.button.x, event.button.y };
        
        int totalWidth = (1920 - 128);
        int textureX = 64;
        int textureY = (1080 * 2) / 3;
        int textureWidth = 0;
        int textureHeight = 0;

        for (auto& [key, texture] : current_tileset->textures) {
            textureWidth = texture->GetWidth() * 4;
            textureHeight = texture->GetHeight() * 4;

            SDL_Rect textureRect = {textureX, textureY, textureWidth, textureHeight};

            if (SDL_PointInRect(&mousePos, &textureRect)) {
                selected_texture = key;
                return;
            } else if (SDL_PointInRect(&mousePos, &s_button.rect)) {
                running = false;
                save_on_exit = true;
                return;
            }

            textureX += totalWidth / current_tileset->textures.size();
        }

        if (tiles_grid.contains(mousePos)) {
            std::cout << selected_texture << " at " << mousePos.x << ", " << mousePos.y; 
            uint16_t aligned_x = (mousePos.x - tiles_grid.x) / TILE_SIZE;
            uint16_t aligned_y = (mousePos.y - tiles_grid.y) / TILE_SIZE;
            std::cout << " - Coords: (" << aligned_x << ", " << aligned_y << ")\n"; 
            tiles.add_tile(aligned_x, aligned_y, selected_texture);
        } else {
            selected_texture = "";
        }
    }
}

void Editor::save() {
    YAML::Node root;
    root["n_tiles_x"] = 16;
    root["n_tiles_y"] = 16;
    root["tileset"] = 0;
    root["items"] = YAML::Node(YAML::NodeType::Sequence);
    for (auto& [coord, tile] : tiles.tiles_map) {
        YAML::Node node;
        node["x"] = coord.first;
        node["y"] = coord.second;
        node["type"] = tile;
        root["items"].push_back(node);
    }

    std::ofstream fout(out_file);
    fout << root;
    fout.close();
}

int Editor::run() {
    try {
        SDL_Event event;
        while (running) {
            renderer.SetDrawColor(0, 0, 0, 255);
            renderer.Clear();
            tiles_grid.draw(renderer);
            draw_textures();
            draw_tiles();
            s_button.draw();
            renderer.Present();

            if (SDL_WaitEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    handle_event(event);
                }
            }

            if (save_on_exit) { save(); }
        }
    } catch (Exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}