#ifndef COMMON_CLIENT_ACTIONS_H
#define COMMON_CLIENT_ACTIONS_H

#include <cstdint>
#include <string>

enum class ClientActionType : uint16_t {
    UNDEFINED = 0,
    CREATE_GAME,   // Enums are assigned consecutive values by default
    JOIN_GAME,     // this number 3
    SEND_MESSAGE,  // 4
    MOVE_RIGHT,
    MOVE_LEFT,
    JUMP,
    SHOOT,
    FLAP, // aletear
    LAY, // tirarse al piso,
    LOOK_UP,
    STOP_MOVING_RIGHT,
    STOP_MOVING_LEFT,
    STOP_JUMPING,
    STOP_SHOOTING,
    STOP_FLAPPING,
    STAND_UP,
    STOP_LOOKING_UP
};

class ActionMessage {
public:
    ClientActionType type;
    std::string opt_message;

    ActionMessage(const ClientActionType &t, const std::string &m) : type(t), opt_message(m) {}
    ActionMessage() : type(ClientActionType::UNDEFINED) {}
    ~ActionMessage() {}
};

#endif // COMMON_CLIENT_ACTIONS_H
