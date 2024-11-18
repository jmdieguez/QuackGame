#ifndef CHEAT_STORAGE_H
#define CHEAT_STORAGE_H

#include <vector>
#include <string>
#include <map>
#include <cctype>
#include "../../../../common/client_actions.h"
#include "../../../../common/queue.h"

class CheatStorage
{
private:
    std::string cheat_build;
    std::map<std::string, ClientActionType> cheats;

public:
    CheatStorage();
    void add_input(std::string input);
    void active_cheat(Queue<ClientActionType> &queue_sender);
    void send_message(Queue<ClientActionType> &queue_sender, ClientActionType &value);
    ~CheatStorage();
};

#endif // CHEAT_STORAGE_H