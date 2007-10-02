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

    /* !
    less-than operator so that the struct can be used in associative comtainers
    */
//    bool operator<( const struct six_byte& other ) const
//    {
//        u_short h = (this->U_main.S_uchar.b1 << 8) || this->U_main.S_uchar.b2;
//        u_long l = (this->U_main.S_uchar.b3 << 16)
//                        || (this->U_main.S_uchar.b4 << 12)
//                        || (this->U_main.S_uchar.b5 << 8)
//                        || (this->U_main.S_uchar.b6);
//
//        u_short oh = (other.U_main.S_uchar.b1 << 8) || other.U_main.S_uchar.b2;
//        u_long ol = (other.U_main.S_uchar.b3 << 16)
//                        || (other.U_main.S_uchar.b4 << 12)
//                        || (other.U_main.S_uchar.b5 << 8)
//                        || (other.U_main.S_uchar.b6);
//        if ( (h < oh) || ( (h == oh) && (l < ol) ) )
//        {
//            return true;
//        }
//        return false;
//    };
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
