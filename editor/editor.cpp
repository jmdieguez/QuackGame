#include "editor.h"
#include <yaml-cpp/yaml.h>
#include <fstream>

#include "../ui/defs.h"

void Editor::draw_tiles() {
    for (auto& [coord, tile] : tiles.tiles_map) {
        uint16_t x = tiles_grid.x + (coord.first * TILE_SIZE);
        uint16_t y = tiles_grid.y + (coord.second * TILE_SIZE);
        std::shared_ptr texture = current_tileset->textures[tile];

        renderer.Copy(*texture,
                    Rect(0, 0, current_tileset->areas[tile].w, current_tileset->areas[tile].h),
                    Rect(x, y, texture->GetWidth() * 2, texture->GetHeight() * 2));
    }

    for (auto& [coord, spawn] : tiles.spawns_map) {
        uint16_t x = tiles_grid.x + (coord.first * TILE_SIZE);
        uint16_t y = tiles_grid.y + (coord.second * TILE_SIZE);
        if (spawn == Spawn::DUCK_SPAWN) {
            int width = duck_texture.GetWidth();
            int height = duck_texture.GetHeight();
            renderer.Copy(duck_texture,
                          Rect(0, 0, width, height),
                          Rect(x, y, width, height)
                         );
        } else if (spawn == Spawn::GUN_SPAWN) {
            int width = gun_spawn_texture.GetWidth();
            int height = gun_spawn_texture.GetHeight();
            renderer.Copy(gun_spawn_texture,
                          Rect(0, 0, width, height),
                          Rect(x + 2, y + TILE_SIZE - height, width, height)
                         );
        }
    }

    for (auto& [coord, box] : tiles.boxes_map) {
        uint16_t x = tiles_grid.x + (coord.first * TILE_SIZE);
        uint16_t y = tiles_grid.y + (coord.second * TILE_SIZE);
        renderer.Copy(box_texture,
                      Rect(0, 0, 16, 16),
                      Rect(x, y, 32, 32)
        );
    }
}

void Editor::draw_textures() {
    int totalWidth = (1920 - 128);
    int textureX = 64;
    int textureY = (1080 * 2) / 3;

    for (auto& [key, texture] : current_tileset->textures) {
        SDL_Color textColor = (key == selected_texture) ? BLUE : WHITE;
        Texture textTexture(renderer, font.RenderText_Blended(titles[key], textColor));
        int textPosX = textureX + ((texture->GetWidth() * 3) / 2);
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

void Editor::unselect() {
    selected_texture = Component::NONE;
    save_button.unselect();
    delete_button.unselect();
    duck_button.unselect();
    gun_button.unselect();
    box_button.unselect();
}

void Editor::handle_selection(const SDL_Point &mousePos) {        
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
            unselect();
            selected_texture = key;
            state = EditorState::CREATING_COMPONENTS;
            return;
        }
        textureX += totalWidth / current_tileset->textures.size();
    }

    if (SDL_PointInRect(&mousePos, &save_button.rect)) {
        unselect();
        save_button.select();
        running = false;
        save_on_exit = true;
        return;
    } else if (SDL_PointInRect(&mousePos, &delete_button.rect)) {
        unselect();
        delete_button.select();
        state = EditorState::CLEANING_TILES;
        return;
    }  else if (SDL_PointInRect(&mousePos, &duck_button.rect)) {
        unselect();
        duck_button.select();
        state = EditorState::CREATING_DUCK_SPAWNS;
        return;
    }  else if (SDL_PointInRect(&mousePos, &gun_button.rect)) {
        unselect();
        gun_button.select();
        state = EditorState::CREATING_GUN_SPAWNS;
        return;
    } else if (SDL_PointInRect(&mousePos, &box_button.rect)) {
        unselect();
        box_button.select();
        state = EditorState::CREATING_BOXES;
        return;
    }
}

void Editor::handle_event(const SDL_Event& event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        SDL_Point mousePos = { event.button.x, event.button.y };
        handle_selection(mousePos);
        if (tiles_grid.contains(mousePos)) {
            std::pair<uint16_t, uint16_t> pair = 
                std::make_pair((mousePos.x - tiles_grid.x) / TILE_SIZE, (mousePos.y - tiles_grid.y) / TILE_SIZE);
            
            if (state == EditorState::CREATING_COMPONENTS) {
                tiles.tiles_map[pair] = selected_texture;
            } else if (state == EditorState::CLEANING_TILES) {
                tiles.tiles_map.erase(pair);
                tiles.spawns_map.erase(pair);
                tiles.boxes_map.erase(pair);
            } else if (state == EditorState::CREATING_DUCK_SPAWNS) {
                tiles.spawns_map[pair] = Spawn::DUCK_SPAWN;
            } else if (state == EditorState::CREATING_GUN_SPAWNS) {
                tiles.spawns_map[pair] = Spawn::GUN_SPAWN;
            } else if (state == EditorState::CREATING_BOXES) {
                tiles.boxes_map[pair] = Box::BOX_4_HP;
            }
        }
    } else if (event.button.button == SDL_BUTTON_RIGHT) {
        unselect();
    }
}

void Editor::save() {
    YAML::Node root;
    root["n_tiles_x"] = 32;
    root["n_tiles_y"] = 16;
    root["tileset"] = current_style;
    
    root["components"] = YAML::Node(YAML::NodeType::Sequence);
    for (auto& [coord, tile] : tiles.tiles_map) {
        YAML::Node node;
        node["x"] = coord.first;
        node["y"] = coord.second;
        node["type"] = tile;
        root["components"].push_back(node);
    }

    root["spawns"] = YAML::Node(YAML::NodeType::Sequence);
    for (auto& [coord, spawn] : tiles.spawns_map) {
        YAML::Node node;
        node["x"] = coord.first;
        node["y"] = coord.second;
        node["type"] = spawn;
        root["spawns"].push_back(node);
    }

    root["boxes"] = YAML::Node(YAML::NodeType::Sequence);
    for (auto& [coord, box] : tiles.boxes_map) {
        YAML::Node node;
        node["x"] = coord.first;
        node["y"] = coord.second;
        root["boxes"].push_back(node);
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
            save_button.draw(w_width);
            duck_button.draw(w_width);
            gun_button.draw(w_width);
            box_button.draw(w_width);
            delete_button.draw(w_width);
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