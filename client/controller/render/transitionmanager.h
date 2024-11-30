//
// Created by trini-taller on 11/30/24.
//

#ifndef TRANSITIONMANAGER_H
#define TRANSITIONMANAGER_H


#include <SDL2pp/SDL2pp.hh>

class TransitionManager {
public:
    TransitionManager(SDL2pp::Renderer &renderer);
    void fadeTransition(int duration, bool fadeOut);
    void drawTransitionOverlay();

private:
    SDL2pp::Renderer &renderer;
    SDL2pp::Texture transitionTexture;
    int alpha;
    void render_next_level_text();
};

#endif //TRANSITIONMANAGER_H
