#include "cheatstorage.h"
#define CHEAT_MAX_SIZE 2

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

CheatStorage::CheatStorage()
{
    cheats["ak"] = ClientActionType::SPAWN_AK;
    cheats["sh"] = ClientActionType::SPAWN_SHOTGUN;
    cheats["gr"] = ClientActionType::SPAWN_GRENADE;
    cheats["ba"] = ClientActionType::SPAWN_BANANA;
    cheats["co"] = ClientActionType::SPAWN_COWBOY_PISTOL;
    cheats["du"] = ClientActionType::SPAWN_DUELING_PISTOL;
    cheats["ma"] = ClientActionType::SPAWN_MAGNUM;
    cheats["pe"] = ClientActionType::SPAWN_PEW_PEW_LASER;
    cheats["sn"] = ClientActionType::SPAWN_SNIPER;
    cheats["ri"] = ClientActionType::SPAWN_LASER_RIFLE;
}

void CheatStorage::add_input(std::string input)
{
    cheat_build += std::tolower(input.c_str()[0]);
    if (cheat_build.size() > CHEAT_MAX_SIZE)
        cheat_build.erase(0, 1);
}

void CheatStorage::active_cheat(GameContext &game_context)
{
    for (auto &[cheat, value] : cheats)
        if (cheat == cheat_build)
            send_message(game_context, value);
}

void CheatStorage::send_message(GameContext &game_context, ClientActionType &value)
{
    game_context.push_message(value);
}

CheatStorage::~CheatStorage()
{
}
