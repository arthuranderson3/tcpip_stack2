#include "net.h"
#include "impl/netimpl.h"
#include <cstring>
#include <random>
#include <sstream>
#include <string>

Mac::Mac() : impl_(new MacImpl) { Mac_init(impl_); }
Mac::~Mac() { delete impl_; }

Mac Mac::MakeRandom() {
  Mac m;
  Mac_random_addr(m.impl_);
  return m;
}

std::string Mac::Hex() const {
  char buf[MacImpl::kAddrStrLen];
  Mac_get_addr(impl_, buf);
  return {buf};
}

std::istream &Mac::FromStream(std::istream &is, Mac &m) {
  int idx = 0;
  std::string hex_str;
  std::getline(is, hex_str);
  Mac_set_addr(m.impl_, hex_str.c_str());
  return is;
}

IPv4::IPv4(const char *addr) : impl_(new IPv4Impl) {
  IPv4_init(impl_);
  IPv4_set_addr(impl_, addr);
}

IPv4::IPv4(const std::string &addr) : IPv4(addr.c_str()) {}
IPv4::~IPv4() { delete impl_; }

std::string IPv4::GetDotAddress() const {
  char tmp[IPv4Impl::kAddrStrLen];
  std::memset(tmp, 0, IPv4Impl::kAddrStrLen);
  IPv4_get_addr_str(impl_, tmp);
  std::string retval(tmp);
  return retval;
}

uint32_t IPv4::GetAddress() const { return impl_->addr; }

struct SubnetImpl {
  SubnetImpl(const char *addr, uint8_t m) : ipv4_(new IPv4Impl), mask(m) {
    IPv4_init(ipv4_);
    IPv4_set_addr(ipv4_, addr);
  }
  IPv4Impl *ipv4_;
  uint8_t mask;
};

Subnet::Subnet(const char *ip, uint8_t mask)
    : impl_(new SubnetImpl(ip, mask)) {}

Subnet::~Subnet() {
  delete impl_;
  impl_ = nullptr;
}

std::string Subnet::GetDotSubnetAddress() const {
  char ip_addr[kSubnetAddrStrLen];
  Subnet_get_addr_str(impl_->ipv4_, impl_->mask, ip_addr);
  return {ip_addr};
}

std::string Subnet::GetDotSubnetMask() const {
  char ip_addr[IPv4Impl::kAddrStrLen];
  Subnet_get_mask_str(impl_->mask, ip_addr);
  return {ip_addr};
}

uint32_t Subnet::GetSubnetMask() const {
  uint32_t subnet_mask;
  Subnet_get_mask(impl_->mask, &subnet_mask);
  return subnet_mask;
}

uint32_t Subnet::GetNetworkId() const {
  uint32_t subnet_id;
  Subnet_get_network_id(impl_->ipv4_, impl_->mask, &subnet_id);
  return subnet_id;
}

std::string Subnet::GetDotNetworkId() const {
  char subnet_addr[IPv4Impl::kAddrStrLen];
  Subnet_get_network_id_str(impl_->ipv4_, impl_->mask, subnet_addr);
  return {subnet_addr};
}

uint32_t Subnet::GetBroadcastAddress() const {
  uint32_t broadcast = 0;
  Subnet_get_broadcast_addr(impl_->mask, &broadcast);
  return broadcast;
}

std::string Subnet::GetDotBroadcastAddress() const {
  char ip_addr[IPv4Impl::kAddrStrLen];
  Subnet_get_broadcast_addr_str(impl_->mask, ip_addr);
  return {ip_addr};
}

uint32_t Subnet::GetMaxNumberOfAddresses() const {
  uint32_t count;
  Subnet_get_max_count(impl_->mask, &count);
  return count;
}