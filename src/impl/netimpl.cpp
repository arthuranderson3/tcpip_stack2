#include "netimpl.h"

#include <arpa/inet.h>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <netinet/in.h>
#include <random>
#include <sys/socket.h>
#include <sys/types.h>

const uint8_t IPv4Impl::kAddrStrLen = INET_ADDRSTRLEN;

void Mac_init(mac_impl_ptr_t ptr) {
  std::memset(ptr->addr, 0, MacImpl::kAddrLen);
}

bool Mac_set_addr(mac_impl_ptr_t ptr, const char *addr) {
  Mac_init(ptr);
  char str_buf[MacImpl::kAddrStrLen];
  std::memset(str_buf, 0, MacImpl::kAddrStrLen);
  std::memcpy(str_buf, addr, MacImpl::kAddrStrLen);

  uint32_t idx = 0;
  char *str = str_buf;
  char *token = strsep(&str, ":");
  do {
    char *end;
    int16_t v = strtol(token, &end, 16);
    ptr->addr[idx++] = static_cast<uint8_t>(v);
  } while ((token = strsep(&str, ":")) != nullptr && idx < MacImpl::kAddrLen);
  return true;
}

bool Mac_get_addr(mac_impl_ptr_t ptr, char *addr) {
  memset(addr, 0, MacImpl::kAddrStrLen);
  sprintf(addr, "%.02x:%.02x:%.02x:%.02x:%.02x:%.02x", ptr->addr[0],
          ptr->addr[1], ptr->addr[2], ptr->addr[3], ptr->addr[4], ptr->addr[5]);
  return true;
}

bool Mac_random_addr(mac_impl_ptr_t ptr) {
  std::random_device rd;  // a seed source for the random number engine
  std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<uint32_t> distrib(0, 0xFF);

  for (int i = 0; i < MacImpl::kAddrLen; i++) {
    uint32_t v = distrib(gen);
    ptr->addr[i] = static_cast<uint8_t>(v);
  }
  return true;
}

bool Mac_set_broadcast_addr(mac_impl_ptr_t ptr) {
  for (int i = 0; i < MacImpl::kAddrLen; i++) {
    ptr->addr[i] = 0xFF;
  }
}

void IPv4_init(ip_impl_ptr_t ptr) {
  ptr->addr = 0;
  ptr->port = 0;
}

bool IPv4_get_presentation_str(uint32_t ipv4, char *addr) {
  memset(addr, 0, IPv4Impl::kAddrStrLen);
  return inet_ntop(AF_INET, &ipv4, addr, IPv4Impl::kAddrStrLen) != NULL;
}

bool IPv4_set_addr(ip_impl_ptr_t ptr, const char *addr) {
  static char s_ip_addr[IPv4Impl::kAddrStrLen];
  std::memset(s_ip_addr, '\0', IPv4Impl::kAddrStrLen);
  std::memcpy(s_ip_addr, addr, IPv4Impl::kAddrStrLen);
  return inet_pton(AF_INET, s_ip_addr, &ptr->addr) == 1;
}

bool IPv4_get_addr_str(ip_impl_ptr_t ptr, char *addr) {
  return IPv4_get_presentation_str(ptr->addr, addr);
}

void IPv4_set_port(ip_impl_ptr_t ptr, uint16_t port) {
  ptr->port = htons(port);
}

void IPv4_get_port(ip_impl_ptr_t ptr, uint16_t &port) {
  port = ntohs(ptr->port);
}

/**
 * "192.168.1.2/24"
 * */
#define SUBNET_ADDRSTRLEN = INET_ADDSTRLEN + 3;

bool Subnet_get_addr_str(ip_impl_ptr_t ip4, uint8_t mask, char *addr) {
  std::memset(addr, 0, kSubnetAddrStrLen);
  char ip_buf[IPv4Impl::kAddrStrLen];
  IPv4_get_addr_str(ip4, ip_buf);
  sprintf(addr, "%s/%d", ip_buf, mask);
}

bool Subnet_get_mask(uint8_t mask, uint32_t *subnet_mask) {
  uint8_t subnet = 32 - mask;
  uint32_t full_mask = 0xFFFFFFFF;
  uint32_t hmask = full_mask << subnet;
  *subnet_mask = htonl(hmask);
  return true;
}

bool Subnet_get_mask_str(uint8_t mask, char *addr) {
  uint32_t subnet_mask = 0;
  Subnet_get_mask(mask, &subnet_mask);
  return IPv4_get_presentation_str(subnet_mask, addr);
}

bool Subnet_get_broadcast_addr(uint8_t mask, uint32_t *addr) {
  uint32_t subnet_mask = 0;
  Subnet_get_mask(mask, &subnet_mask);
  *addr = ~subnet_mask;
  return true;
}

bool Subnet_get_broadcast_addr_str(uint8_t mask, char *addr) {
  uint32_t broadcast = 0;
  Subnet_get_broadcast_addr(mask, &broadcast);
  return IPv4_get_presentation_str(broadcast, addr);
}

bool Subnet_get_network_id(ip_impl_ptr_t ip4, uint8_t mask, uint32_t *net_id) {
  uint32_t subnet_mask = 0;
  Subnet_get_mask(mask, &subnet_mask);
  *net_id = ip4->addr & subnet_mask;
  return true;
}

bool Subnet_get_network_id_str(ip_impl_ptr_t ip4, uint8_t mask, char *addr) {
  uint32_t net_id = 0;
  Subnet_get_network_id(ip4, mask, &net_id);
  return IPv4_get_presentation_str(net_id, addr);
}

bool Subnet_get_max_count(uint8_t mask, uint32_t *count) {
  float power = 32.0 - static_cast<float>(mask);
  *count = static_cast<int32_t>(std::pow(2.0, power)) - 2;
}
