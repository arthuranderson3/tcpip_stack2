#ifndef __TCPIP_STACK_MAC__
#define __TCPIP_STACK_MAC__

#include <iostream>
#include <string>

/**
 * Mac address
 * */

class Mac {
public:
  static Mac MakeRandom();
  static std::istream &FromStream(std::istream &is, Mac &m);
  std::string Hex() const;

private:
  uint8_t addr[6];
};

#endif // __TCPIP_STACK_MAC__
