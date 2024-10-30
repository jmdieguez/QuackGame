#ifndef EDITOR_SAVE_BUTTON_H
#define EDITOR_SAVE_BUTTON_H

#include <SDL2pp/SDL2pp.hh>

#define FONT_PATH "var/quackgame/04B_30.TTF"

using namespace SDL2pp;

class SaveButton {
private:
    SDL_Color textColor = SDL_Color{255, 255, 255, 255};
    Font font;
    Renderer &renderer;
    Texture textTexture;
public:
    const Rect rect;

    SaveButton(Renderer &r) : font(FONT_PATH, 32), renderer(r), textTexture(r, font.RenderText_Blended("Save And Exit", textColor)),
        rect(10, 10, textTexture.GetWidth(), textTexture.GetHeight()) {}

    void draw() {
        renderer.Copy(textTexture, NullOpt, rect);
    }
};

#endif // EDITOR_SAVE_BUTTON_H
