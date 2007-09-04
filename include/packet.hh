#ifndef __PACKET_HH__
#define __PACKET_HH__

#include "defines.hh"
#include "ethernetiiframe.hh"
#include "ipv4datagram.hh"

class Packet
{
private:
  u_char* data;
  
public:
  Packet(u_char* data);
  
  inline u_char* getData()
  {
    return data;
  };
};

#endif
