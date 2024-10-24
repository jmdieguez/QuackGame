#include "gamecontext.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

GameContext::GameContext() : is_right_direction(true),
                             is_running(false),
                             is_bent_down(false)
{
}

bool GameContext::get_is_running() const
{
    return is_running;
}

bool GameContext::get_is_right_direction() const
{
    return is_right_direction;
}

bool GameContext::get_is_bent_down() const
{
    return is_bent_down;
}

void GameContext::set_is_running(bool new_value)
{
    is_running = new_value;
}

void GameContext::set_is_right_direction(bool new_value)
{
    is_right_direction = new_value;
}

void GameContext::set_is_bent_down(bool new_value)
{
    is_bent_down = new_value;
}

GameContext::~GameContext()
{
}
