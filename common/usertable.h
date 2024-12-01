#ifndef USER_TABLE_H
#define USER_TABLE_H

#include <string>
#include <cstdint>

class UserTable
{
public:
    std::string color_name;
    uint16_t round_wins;

    UserTable() {};
    ~UserTable() {};
};

#endif // USER_TABLE_H