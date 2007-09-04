#ifndef __PACKET_HH__
#define __PACKET_HH__

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
