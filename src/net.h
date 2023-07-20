#ifndef __TCPIP_STACK_NET__
#define __TCPIP_STACK_NET__

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

  Mac();
  ~Mac();

private:
  struct MacImpl *impl_;
};

/**
 * IPv4
 * */
class IPv4 {
public:
  IPv4(const char *addr);
  IPv4(const std::string &addr);
  ~IPv4();
  /**
   * GetDotAddress 192.168.0.2
   * */
  std::string GetDotAddress() const;
  /**
   * GetAddress in network byte order
   * */
  uint32_t GetAddress() const;

private:
  struct IPv4Impl *impl_;
};

/**
 * Subnet
 * */
class Subnet {
public:
  Subnet(const char *ip, uint8_t mask);
  ~Subnet();
  /**
   * GetDotSubnetAddress 192.168.0.2/24
   * */
  std::string GetDotSubnetAddress() const;
  /**
   * GetDotSubnetMask 255.255.255.0
   * */
  std::string GetDotSubnetMask() const;
  /**
   * GetSubnetMask in network byte order
   * */
  uint32_t GetSubnetMask() const;
  /**
   * GetNetworkId in network byte order
   * */
  uint32_t GetNetworkId() const;
  /**
   * GetNetworkIdStr 192.168.1.0
   * */
  std::string GetDotNetworkId() const;
  /**
   * GetBroadcastAddress in network byte order
   * */
  uint32_t GetBroadcastAddress() const;
  /**
   * GetBroadcastAddress 192.168.1.255
   * */
  std::string GetDotBroadcastAddress() const;
  /**
   * GetMaxNumberOfAddresses 255
   * */
  uint32_t GetMaxNumberOfAddresses() const;

private:
  struct SubnetImpl *impl_;
};

#endif // __TCPIP_STACK_NET__
