#include <gtest/gtest.h>

#include "netimpl.h"
#include <iostream>

TEST(MacImpl, test_init) {
  mac_impl_ptr_t ptr = new MacImpl;
  Mac_init(ptr);
  EXPECT_EQ(ptr->addr[0], 0);
  EXPECT_EQ(ptr->addr[1], 0);
  EXPECT_EQ(ptr->addr[2], 0);
  EXPECT_EQ(ptr->addr[3], 0);
  EXPECT_EQ(ptr->addr[4], 0);
  EXPECT_EQ(ptr->addr[5], 0);
}

TEST(MacImpl, test_set_addr) {
  mac_impl_ptr_t ptr = new MacImpl;
  Mac_init(ptr);
  EXPECT_TRUE(Mac_set_addr(ptr, "9e:2a:bd:d9:d9:6f"));
  EXPECT_EQ(ptr->addr[0], 0x9e);
  EXPECT_EQ(ptr->addr[1], 0x2a);
  EXPECT_EQ(ptr->addr[2], 0xbd);
  EXPECT_EQ(ptr->addr[3], 0xd9);
  EXPECT_EQ(ptr->addr[4], 0xd9);
  EXPECT_EQ(ptr->addr[5], 0x6f);
}

TEST(MacImpl, test_get_addr_str) {
  mac_impl_ptr_t ptr = new MacImpl;
  Mac_init(ptr);
  EXPECT_TRUE(Mac_set_addr(ptr, "9e:2a:bd:d9:d9:6f"));
  char str_buf[MacImpl::kAddrStrLen];
  EXPECT_TRUE(Mac_get_addr(ptr, str_buf));
  EXPECT_STREQ("9e:2a:bd:d9:d9:6f", str_buf);
}

TEST(MacImpl, test_random_addr) {
  mac_impl_ptr_t ptr = new MacImpl;
  Mac_random_addr(ptr);
  char str_buf[MacImpl::kAddrStrLen];
  EXPECT_TRUE(Mac_get_addr(ptr, str_buf));
}

TEST(MacImpl, test_set_broadcast_addr) {
  mac_impl_ptr_t ptr = new MacImpl;
  Mac_set_broadcast_addr(ptr);
  for (uint i = 0; i < MacImpl::kAddrLen; i++) {
    EXPECT_EQ(ptr->addr[i], 0xFF);
  }
}

TEST(IPv4Impl, test_init) {
  ip_impl_ptr_t ptr = new IPv4Impl;
  IPv4_init(ptr);
  EXPECT_EQ(ptr->addr, 0);
  EXPECT_EQ(ptr->port, 0);
}

TEST(IPv4Impl, test_set_addr) {
  ip_impl_ptr_t ptr = new IPv4Impl;
  IPv4_init(ptr);
  EXPECT_TRUE(IPv4_set_addr(ptr, "192.168.1.1"));
  EXPECT_EQ(ptr->addr, 0x0101a8C0);
}

TEST(IPv4Impl, test_get_addr_str) {
  ip_impl_ptr_t ptr = new IPv4Impl;
  IPv4_init(ptr);
  EXPECT_TRUE(IPv4_set_addr(ptr, "192.168.1.1"));
  char str_buff[IPv4Impl::kAddrStrLen];
  EXPECT_TRUE(IPv4_get_addr_str(ptr, str_buff));
  EXPECT_STREQ("192.168.1.1", str_buff);
}

TEST(IPv4Impl, test_set_port) {
  ip_impl_ptr_t ptr = new IPv4Impl;
  IPv4_init(ptr);
  IPv4_set_port(ptr, 20);
  EXPECT_EQ(ptr->port, 0x1400); // Network byte order
  uint16_t port;
  IPv4_get_port(ptr, port);
  EXPECT_EQ(port, 0x14); // Host byte order
}

TEST(Subnet, test_get_addr_str) {
  ip_impl_ptr_t ipv4 = new IPv4Impl;
  IPv4_init(ipv4);
  IPv4_set_addr(ipv4, "192.168.5.154");
  uint8_t mask = 26;
  char subnet_addr[kSubnetAddrStrLen];
  Subnet_get_addr_str(ipv4, mask, subnet_addr);
  EXPECT_STREQ("192.168.5.154/26", subnet_addr);
}

TEST(Subnet, test_get_mask_str) {
  char subnet_mask[16];
  Subnet_get_mask_str(24, subnet_mask);
  EXPECT_STREQ("255.255.255.0", subnet_mask);
  Subnet_get_mask_str(26, subnet_mask);
  EXPECT_STREQ("255.255.255.192", subnet_mask);
}

TEST(Subnet, test_get_mask) {
  uint32_t subnet_mask = 0;
  uint32_t expect = 0x00FFFFFF;
  Subnet_get_mask(24, &subnet_mask);
  EXPECT_EQ(expect, subnet_mask);
}

TEST(Subnet, test_get_broadcast) {
  uint32_t broadcast = 0;
  // If little endian 0x000000FF
  // NOTE: network byte order - Big Endian
  Subnet_get_broadcast_addr(24, &broadcast);
  EXPECT_EQ(0xFF000000, broadcast);

  // NOTE 30 is used in Point to Point links
  //   00 is used for Network ID
  //   11 is used for the broadcast id
  //   b01, b10 are used for each end of a point to point interface
  broadcast = 0;
  Subnet_get_broadcast_addr(30, &broadcast);
  EXPECT_EQ(0x03000000, broadcast);
}

TEST(Subnet, test_get_network_id) {
  ip_impl_ptr_t ipv4 = new IPv4Impl;
  IPv4_init(ipv4);
  IPv4_set_addr(ipv4, "192.168.5.154");
  uint8_t mask = 24;
  uint32_t net_id = 0;
  Subnet_get_network_id(ipv4, mask, &net_id);
  uint32_t exp_id = 0x0005a8c0;
  EXPECT_EQ(exp_id, net_id);
}

TEST(Subnet, test_get_network_id_str) {
  ip_impl_ptr_t ipv4 = new IPv4Impl;
  IPv4_init(ipv4);
  IPv4_set_addr(ipv4, "192.168.5.154");
  uint8_t mask = 24;
  char subnet_addr[kSubnetAddrStrLen];
  Subnet_get_network_id_str(ipv4, mask, subnet_addr);
  EXPECT_STREQ("192.168.5.0", subnet_addr);
}

TEST(Subnet, test_get_max_count) {
  uint32_t count = 0;
  Subnet_get_max_count(24, &count);
  EXPECT_EQ(254, count);
  Subnet_get_max_count(30, &count);
  EXPECT_EQ(2, count);
}