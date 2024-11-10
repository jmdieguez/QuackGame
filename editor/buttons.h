#ifndef EDITOR_SAVE_BUTTON_H
#define EDITOR_SAVE_BUTTON_H

#include <SDL2pp/SDL2pp.hh>

#define FONT_PATH "var/quackgame/04B_30.TTF"

using namespace SDL2pp;

class Button {
protected:
    SDL_Color textColor = SDL_Color{255, 255, 255, 255};
    Font font;
    Renderer &renderer;
    Texture textTexture;
    int yOffset;
    Button(Renderer &r, const std::string& text, int y_offset)
        : font(FONT_PATH, 32), renderer(r), textTexture(r, font.RenderText_Blended(text, textColor)), yOffset(y_offset) {}

    void update_rect(const int& w_w) {
        rect = {w_w - 32 - textTexture.GetWidth(), yOffset, textTexture.GetWidth(), textTexture.GetHeight()};
    }

public:
    SDL_Rect rect = {0, 0, 0, 0};
    void draw(const int& w_w) {
        update_rect(w_w);
        renderer.Copy(textTexture, NullOpt, rect);
    }

    void select() {
        SDL_SetTextureColorMod(textTexture.Get(), 255, 0, 0);
    }

    void unselect() {
        SDL_SetTextureColorMod(textTexture.Get(), 255, 255, 255);
    }
};

class SaveButton : public Button {
public:
    SaveButton(Renderer &r) : Button(r, "SAVE AND EXIT", 32) {}
};

class DuckSpawnButton : public Button {
public:
    DuckSpawnButton(Renderer &r) : Button(r, "CREATE DUCK SPAWN", 96) {}
};

class GunSpawnButton : public Button {
public:
    GunSpawnButton(Renderer &r) : Button(r, "CREATE GUN SPAWN", 160) {}
};

class BoxButton : public Button {
public:
    BoxButton(Renderer &r) : Button(r, "CREATE A BOX", 224) {}
};

class DeleteButton : public Button {
public:
    DeleteButton(Renderer &r) : Button(r, "CLEAN A TILE", 288) {}
};


#endif // EDITOR_SAVE_BUTTON_H
