#ifndef CLIENT_COMMAND_TYPE_H
#define CLIENT_COMMAND_TYPE_H

enum class ClientCommandType {
    UNDEFINED = 0, // para inicializar un ClientCommand
    CREATE_GAME,
    JOIN_GAME,
    SEND_MESSAGE,
    MOVE_RIGHT,
    MOVE_LEFT,
    JUMP,
    SHOOT,
    FLAP, // aletear
    LAY, // tirarse al piso
    STOP_MOVING_RIGHT,
    STOP_MOVING_LEFT,
    STOP_JUMPING,
    STOP_SHOOTING,
    STOP_FLAPPING,
    STAND_UP
};

#endif // CLIENT_COMMAND_H
