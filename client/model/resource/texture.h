#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2pp/SDL2pp.hh>
#include <string>

class Texture
{
private:
    SDL2pp::Surface surface;
    SDL2pp::Texture texture;

public:
    explicit Texture(SDL2pp::Renderer &renderer, const std::string &path);
    SDL_Texture *get_texture() const;
    ~Texture();
};

#endif // TEXTURE_H