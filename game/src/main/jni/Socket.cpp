//
// Created by qwerty on 29.10.16.
//

#include "Socket.h"

bool Socket::open(unsigned short port) {
    handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (handle <= 0) {
        printf("failed to create socket\n");
        return false;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons((unsigned short) port);

    if (bind(handle, (const sockaddr *) &address, sizeof(sockaddr_in)) < 0) {
        printf("failed to bind socket\n");
        return false;
    }

    int nonBlocking = 1;
    if (fcntl(handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1) {
        printf("failed to set non-blocking\n");
        return false;
    }

    return true;
}

Socket::Socket() { }

Socket::~Socket() { }

bool Socket::send(Address &address, const void *data, int size) {
    int sentBytes = sendto(handle,
                           (const char *) data,
                           size,
                           0,
                           (sockaddr *) address.getSockAddr(),
                           sizeof(sockaddr));

    if (sentBytes != size) {
        printf("failed to send packet\n");
        return false;
    }

    return true;
}

void Socket::destroy() {
    close(handle);
}

bool Socket::isOpen() const {
    return true;
}
