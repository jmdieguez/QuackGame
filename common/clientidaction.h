#ifndef CLIENT_ID_ACTION_H
#define CLIENT_ID_ACTION_H

#include "client_actions.h"

class ClientIdAction
{
private:
    uint16_t id;
    ClientActionType action;

public:
    ClientIdAction(uint16_t &id, ClientActionType &action) : id(id), action(action) {};
    uint16_t get_id() const
    {
        return id;
    }

    ClientActionType get_action() const
    {
        return action;
    }
    ~ClientIdAction() {};
};

#endif // CLIENT_ID_ACTION_H