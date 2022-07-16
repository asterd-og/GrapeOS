#pragma once

#include <stdint.h>

#define PORT_A 0x3F8
#define PORT_B 0x2F8
#define PORT_C 0x3E8
#define PORT_D 0x2E8

namespace Dbg {
    void setport(int port);
    void enable();
    
    int  rcvd();
    char recv();
    char recv_async();
    int  recv_string(char* buf, int size);
    
    int  transmit_empty();
    void send(char out);
    void send_string(char * out);
    int  printf(const char* fmt, ...);
}