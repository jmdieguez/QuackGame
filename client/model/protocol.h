#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "../common/snapshots.h"
// #include "../common/actions.h"
#include "../common/socket.h"

class ClientProtocol
{
private:
    // Socket &skt;

public:
    ClientProtocol();
    // explicit ClientProtocol(Socket &);
    bool read(uint8_t &info);
    // void send(const ActionMessage &, bool &);
    //  bool readDuck(Duck &);
};

#endif // PROTOCOL_H
