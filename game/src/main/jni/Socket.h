//
// Created by qwerty on 29.10.16.
//

#ifndef PLATFORMER_SOCKET_H
#define PLATFORMER_SOCKET_H

#include "Address.h"

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

class Socket {
public:
    Socket();
    virtual ~Socket();

    bool open(unsigned short port);
    void destroy();
    bool isOpen() const;

    bool send(Address& address, const void * data, int size);

private:
    int handle;
};

#endif //PLATFORMER_SOCKET_H
