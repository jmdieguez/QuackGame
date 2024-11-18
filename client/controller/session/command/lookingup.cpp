#include "lookingup.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

LookingUp::LookingUp()
{
}

void LookingUp::execute(GameContext &game_context)
{
    if (game_context.looking_up)
        return;
    game_context.looking_up = true;
    game_context.push_message(ClientActionType::LOOK_UP);
}

void LookingUp::undo(GameContext &game_context)
{
    game_context.looking_up = false;
    game_context.push_message(ClientActionType::STOP_LOOKING_UP);
}

LookingUp::~LookingUp()
{
}
