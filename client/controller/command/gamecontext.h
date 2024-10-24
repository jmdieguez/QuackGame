#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

class GameContext
{
private:
    bool is_right_direction;
    bool is_running;
    bool is_bent_down;

public:
    GameContext();
    bool get_is_running() const;
    bool get_is_right_direction() const;
    bool get_is_bent_down() const;
    void set_is_running(bool new_value);
    void set_is_right_direction(bool new_value);
    void set_is_bent_down(bool new_value);
    ~GameContext();
};

#endif // GAME_CONTEXT_H