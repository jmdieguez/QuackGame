#ifndef CHEAT_STORAGE_H
#define CHEAT_STORAGE_H

#include <vector>
#include <string>
#include <map>
#include <cctype>
#include "../command/gamecontext.h"
#include "../../../../common/client_actions.h"
#include "../../../../common/queue.h"

class CheatStorage
{
private:
    std::string cheat_build;
    std::map<std::string, ClientActionType> cheats;
    void send_message(GameContext &game_context, ClientActionType &value);

public:
    CheatStorage();
    void add_input(std::string input);
    void active_cheat(GameContext &game_context);
    ~CheatStorage();
};

#endif // CHEAT_STORAGE_H