#ifndef __PACKETACCESS_HH__
#define __PACKETACCESS_HH__

#if defined(WIN32)
#include <winsock2.h>
#endif

/*!
A structure containing six bytes, used to access MAC addresses in packets.

\author Simon Jagoe
*/
struct six_byte
{
    union
    {
        struct
        {
            u_char b1,b2,b3,b4,b5,b6; //! Bytes of the address.
        } S_uchar;
        struct
        {
            u_short high, mid, low; //! 16-bit Words of the address
        } S_ushort;
    } U_main;
};

/*!
A structure containing four bytes, used to access IP addresses in packets.

\author Simon Jagoe
*/
struct four_byte
{
    union
    {
        struct
        {
            u_char b1,b2,b3,b4; //! Four individual bytes
        } S_uchar;
        struct
        {
            unsigned long address; //! A four-byte long integer.
        } S_uint32;
    } U_main;
};

/*!
A struct containing two bytes, used to access all two-byte long fields in headers.

\author Simon Jagoe
*/
struct two_byte
{
    union
    {
        struct
        {
            u_char high,low; //! Individual bytes
        } S_uchar;
//        struct
//        {
//            u_short eType;
//        } S_ushort;
    } U_main;
};

#endif
