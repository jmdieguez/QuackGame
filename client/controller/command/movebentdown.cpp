#include "movebentdown.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveBentDown::MoveBentDown()
{
}

void MoveBentDown::execute(GameContext &game_context)
{
    if (game_context.is_bent_down_pressed())
        return;
    game_context.set_bent_down_active(true);
    game_context.push_message(ClientActionType::LAY);
}

void MoveBentDown::undo(GameContext &game_context)
{
    game_context.set_bent_down_active(false);
    game_context.push_message(ClientActionType::STAND_UP);
}

MoveBentDown::~MoveBentDown()
{
}
