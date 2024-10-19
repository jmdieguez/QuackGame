#ifndef COMMON_CLIENT_COMMAND_H
#define COMMON_CLIENT_COMMAND_H

#include <string>

#include "common_box_id.h"

#define MSG_CODE 3
#define UNDEFINED_CODE 0
#define UNDEFINED_NAME "undefined"
#define UNDEFINED_NAME_LEN 0

class ClientCommand {
public:
    uint8_t code;
    std::string name;
    uint16_t name_len;
    BoxID box_id;

    ClientCommand(const std::string& n, const uint16_t& l, const BoxID& id):
            code(MSG_CODE), name(n), name_len(l), box_id(id) {}

    ClientCommand():
            code(UNDEFINED_CODE),
            name(UNDEFINED_NAME),
            name_len(UNDEFINED_NAME_LEN),
            box_id(BoxID::Undefined) {}

    ~ClientCommand() = default;
};

#endif  // COMMON_CLIENT_COMMAND_H
