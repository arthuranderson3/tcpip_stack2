#ifndef __TCPIP_STACK2_NETIMPL__
#define __TCPIP_STACK2_NETIMPL__
#include <arpa/inet.h>
#include <inttypes.h>
#include <sys/types.h>

/**
 * MacImpl
 * */
struct MacImpl {
  static const uint8_t kAddrLen{6};
  /**
   * 9e:2a:bd:d9:d9:6f
   * */
  static const uint8_t kAddrStrLen{18};
  uint8_t addr[kAddrLen];
};

typedef MacImpl *mac_impl_ptr_t;

void Mac_init(mac_impl_ptr_t ptr);
bool Mac_set_addr(mac_impl_ptr_t ptr, const char *addr);
bool Mac_get_addr(mac_impl_ptr_t ptr, char *addr);
bool Mac_set_broadcast_addr(mac_impl_ptr_t ptr);
bool Mac_random_addr(mac_impl_ptr_t ptr);

/**
 * IPv4Impl
 * */
struct IPv4Impl {
  static const uint8_t kAddrStrLen;
  /**
   * addr is always in network byte order
   * */
  in_addr_t addr;
  /**
   * port is always in netork byte order
   * */
  in_port_t port;
};

typedef struct IPv4Impl *ip_impl_ptr_t;

void IPv4_init(ip_impl_ptr_t ptr);
bool IPv4_get_presentation_str(uint32_t ipv4, char *addr);
bool IPv4_set_addr(ip_impl_ptr_t ptr, const char *addr);
bool IPv4_get_addr_str(ip_impl_ptr_t ptr, char *addr);

void IPv4_set_port(ip_impl_ptr_t ptr, uint16_t port);
void IPv4_get_port(ip_impl_ptr_t ptr, uint16_t &port);

/**
 * Subnet
 * */
static const uint8_t kSubnetAddrStrLen = IPv4Impl::kAddrStrLen + 4;
/**
 * Subnet get addr str [ip addr/mask] [192.168.0.1/24]
 * */
bool Subnet_get_addr_str(ip_impl_ptr_t ip4, uint8_t mask, char *addr);

/**
 * Subnet get mask 24 => 0xFFFFFF00 (Little Endian) 0x00FFFFFF (Big Endian)
 * */
bool Subnet_get_mask(uint8_t mask, uint32_t *addr);
/**
 * Subnet mask 255.255.255.0   == 24
 *             255.255.255.192 == 26
 * */
bool Subnet_get_mask_str(uint8_t mask, char *addr);
/**
 * Subnet_broadcast_addr_str
 * mask - uint8_t - mask
 * addr - char * - the broadcast address this address in this subnet
 * */
bool Subnet_get_broadcast_addr(uint8_t mask, uint32_t *addr);
bool Subnet_get_broadcast_addr_str(uint8_t mask, char *addr);
/**
 * Subnet network id
 * Example...
 * for a class C network with a network id: 193.1.2.0
 * there is a division of 4 subnets within that network.
 * subnet 1 network id: 193.1.2.0
 * subnet 2 network id: 193.1.2.64
 * subnet 3 network id: 193.1.2.128
 * subnet 4 network id: 192.1.2.192
 *
 * 24 bits in network id + 2 bits for subnet network id = 26 bits
 *    which leaves 6 bits for each host id.
 *
 * A subnet mask of 26: 11111111.11111111.11111111.11000000
 * */
bool Subnet_get_network_id(ip_impl_ptr_t ip4, uint8_t mask, uint32_t *net_id);
bool Subnet_get_network_id_str(ip_impl_ptr_t ip4, uint8_t mask, char *addr);

bool Subnet_get_max_count(uint8_t mask, uint32_t *count);

#endif // __TCPIP_STACK2_NETIMPL__