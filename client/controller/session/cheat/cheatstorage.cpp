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
}

void CheatStorage::add_input(std::string input)
{
    cheat_build += std::tolower(input.c_str()[0]);
    if (cheat_build.size() > CHEAT_MAX_SIZE)
        cheat_build.erase(0, 1);
}

void CheatStorage::active_cheat(Queue<ClientActionType> &queue_sender)
{
    for (auto &[cheat, value] : cheats)
        if (cheat == cheat_build)
            send_message(queue_sender, value);
}

void CheatStorage::send_message(Queue<ClientActionType> &queue_sender, ClientActionType &value)
{
    queue_sender.try_push(value);
}

CheatStorage::~CheatStorage()
{
}
