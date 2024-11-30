#ifndef PLAYER_KEY_CONFIG_H
#define PLAYER_KEY_CONFIG_H

#include <SDL_keycode.h>
#include <unordered_map>
#include "command.h"

class PlayerKeyConfig
{
private:
    std::unordered_map<SDL_Keycode, Command *> key_command_map;

public:
    PlayerKeyConfig(const std::unordered_map<SDL_Keycode, Command *> &key_map);
    const std::unordered_map<SDL_Keycode, Command *> &get_key_command_map() const;
    Command *get_command(SDL_Keycode key) const;
    ~PlayerKeyConfig();
};

#endif // PLAYER_KEY_CONFIG_H