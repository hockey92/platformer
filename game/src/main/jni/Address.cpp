//
// Created by qwerty on 29.10.16.
//

#include "Address.h"
#include <arpa/inet.h>

Address::Address(std::string address, unsigned short int port) {
    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(address.c_str());
    sa.sin_port = htons(port);
}

struct sockaddr_in *Address::getSockAddr() {
    return &sa;
}