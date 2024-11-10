#include "lookingup.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

LookingUp::LookingUp()
{
}

void LookingUp::execute(GameContext &game_context)
{
    if (game_context.is_looking_up_pressed())
        return;
    game_context.set_looking_up_active(true);
    game_context.push_message(ClientActionType::LOOK_UP);
}

void LookingUp::undo(GameContext &game_context)
{
    game_context.set_looking_up_active(false);
    game_context.push_message(ClientActionType::STOP_LOOKING_UP);
}

LookingUp::~LookingUp()
{
}
