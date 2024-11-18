#include "movebentdown.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveBentDown::MoveBentDown()
{
}

void MoveBentDown::execute(GameContext &game_context)
{
    if (game_context.is_bent_down)
        return;
    game_context.is_bent_down = true;
    game_context.push_message(ClientActionType::LAY);
}

void MoveBentDown::undo(GameContext &game_context)
{
    game_context.is_bent_down = false;
    game_context.push_message(ClientActionType::STAND_UP);
}

MoveBentDown::~MoveBentDown()
{
}
