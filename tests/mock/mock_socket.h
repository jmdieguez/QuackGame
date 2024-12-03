#ifndef MOCK_SOCKET_H
#define MOCK_SOCKET_H

#include "../../common/socket.h"
#include <gmock/gmock.h>

class MockSocket : public Socket {
public:
 // Constructor matching Socket's constructors
 MockSocket(const char* hostname, const char* servname) : Socket(hostname, servname) {}
 explicit MockSocket(const char* servname) : Socket(servname) {}

 // Mock the methods from the Socket class
 MOCK_METHOD(int, sendall, (const void* data, unsigned int sz, bool* was_closed));
 MOCK_METHOD(int, recvall, (void* data, unsigned int sz, bool* was_closed));
 MOCK_METHOD(int, sendsome, (const void* data, unsigned int sz, bool* was_closed));
 MOCK_METHOD(int, recvsome, (void* data, unsigned int sz, bool* was_closed));
 MOCK_METHOD(Socket, accept, ());
 MOCK_METHOD(void, shutdown, (int how));
 MOCK_METHOD(int, close, ());
};

#endif // MOCK_SOCKET_H