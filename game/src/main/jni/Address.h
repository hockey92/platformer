//
// Created by qwerty on 29.10.16.
//

#ifndef PLATFORMER_ADDRESS_H
#define PLATFORMER_ADDRESS_H

#include <netinet/in.h>
#include <string>

class Address {
public:
    Address(std::string address, unsigned short port);

    struct sockaddr_in *getSockAddr();

private:
    struct sockaddr_in sa;
};

#endif //PLATFORMER_ADDRESS_H
