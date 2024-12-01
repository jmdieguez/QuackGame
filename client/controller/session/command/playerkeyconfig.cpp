#include "playerkeyconfig.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

PlayerKeyConfig::PlayerKeyConfig(const std::unordered_map<SDL_Keycode, Command *> &key_map)
    : key_command_map(key_map) {}

Command *PlayerKeyConfig::get_command(SDL_Keycode key) const
{
    auto it = key_command_map.find(key);
    return (it != key_command_map.end()) ? it->second : nullptr;
}

const std::unordered_map<SDL_Keycode, Command *> &PlayerKeyConfig::get_key_command_map() const
{
    return key_command_map;
}

PlayerKeyConfig::~PlayerKeyConfig() {}