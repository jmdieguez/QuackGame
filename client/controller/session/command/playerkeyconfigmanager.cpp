#include "playerkeyconfigmanager.h"
#include "moveleft.h"
#include "moveright.h"
#include "movebentdown.h"
#include "shoot.h"
#include "drop.h"
#include "grab.h"
#include "lookingup.h"
#include "jump.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

PlayerKeyConfigManager::PlayerKeyConfigManager()
{
    std::unordered_map<SDL_Keycode, Command *> player1_keys = {
        {SDLK_w, new LookingUp()}, {SDLK_a, new MoveLeft()}, {SDLK_d, new MoveRight()}, {SDLK_s, new MoveBentDown()}, {SDLK_t, new Shoot()}, {SDLK_g, new Drop()}, {SDLK_e, new Grab()}, {SDLK_SPACE, new Jump()}};

    std::unordered_map<SDL_Keycode, Command *> player2_keys = {
        {SDLK_UP, new LookingUp()}, {SDLK_LEFT, new MoveLeft()}, {SDLK_RIGHT, new MoveRight()}, {SDLK_DOWN, new MoveBentDown()}, {SDLK_p, new Shoot()}, {SDLK_l, new Drop()}, {SDLK_o, new Grab()}, {SDLK_RSHIFT, new Jump()}};

    player_configs.emplace_back(player1_keys);
    player_configs.emplace_back(player2_keys);
}

const PlayerKeyConfig &PlayerKeyConfigManager::get_player_config(size_t player_index) const
{
    return player_configs[player_index];
}

PlayerKeyConfigManager::~PlayerKeyConfigManager()
{
    for (auto &config : player_configs)
        for (auto &pair : config.get_key_command_map())
            delete pair.second;
}