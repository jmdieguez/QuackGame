#ifndef GAME_MUSIC_H
#define GAME_MUSIC_H

#include <string>
#include <vector>
#include <memory>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Music.hh>

class MusicBox
{
private:
    std::vector<std::string> paths;
    SDL2pp::Mixer &mixer;
    std::unique_ptr<SDL2pp::Music> current_music;
    size_t current_index;
    void play_next();

public:
    explicit MusicBox(SDL2pp::Mixer &mixer);
    void start(unsigned volume);
    ~MusicBox();
};

#endif // GAME_MUSIC_H