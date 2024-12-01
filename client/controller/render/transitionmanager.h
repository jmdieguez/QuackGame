
#ifndef TRANSITIONMANAGER_H
#define TRANSITIONMANAGER_H


#include <SDL2pp/SDL2pp.hh>

class TransitionManager {
public:
    TransitionManager(SDL2pp::Renderer &renderer, SDL2pp::Font &font);
    void fadeTransition();
    void drawTransitionOverlay();

private:
    SDL2pp::Renderer &renderer;
    SDL2pp::Font& font;
    SDL2pp::Texture transitionTexture;
    int alpha;
    void render_next_level_text();
};

#endif //TRANSITIONMANAGER_H
