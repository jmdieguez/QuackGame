#include "gamecontext.h"
#include <iostream>

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

GameContext::GameContext(uint16_t &id, Queue<ClientIdAction> &queue_sender) : id(id), queue_sender(queue_sender), looking_up(false), left_direction(false), right_direction(false),
                                                                              is_bent_down(false), is_shooting(false), is_droping(false), is_grabing(false),
                                                                              is_jumping(false)

{
}

void GameContext::push_message(ClientActionType action)
{
    ClientIdAction client_id_action(id, action);
    std::cout << "Estoy enviando con el id: " << (int)client_id_action.get_id() << std::endl;
    queue_sender.try_push(client_id_action);
}

GameContext::~GameContext()
{
}
