#include "movebentdown.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveBentDown::MoveBentDown()
{
}

void MoveBentDown::execute(GameContext &game_context)
{
    game_context.push_message(ClientActionType::BENT_DOWN);
}

void MoveBentDown::undo(GameContext &game_context)
{
    game_context.push_message(ClientActionType::STAND_UP);
}

MoveBentDown::~MoveBentDown()
{
}
