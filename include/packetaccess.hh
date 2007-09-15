#ifndef __PACKETACCESS_HH__
#define __PACKETACCESS_HH__

#if defined(WIN32)
#include <winsock2.h>
#endif

struct six_byte
{
    u_char b1,b2,b3,b4,b5,b6;
};

struct four_byte
{
    union
    {
        struct
        {
            u_char b1,b2,b3,b4;
        } S_uchar;
        struct
        {
            unsigned long address;
        } S_uint32;
    } U_main;
};

struct two_byte
{
    union
    {
        struct
        {
            u_char high,low;
        } S_uchar;
        struct
        {
            u_short eType;
        } S_ushort;
    } U_main;
};

#endif
