#include <gtest/gtest.h>

#include "net.h"
#include <cassert>
#include <iostream>
#include <sstream>

TEST(Mac, test_make_mac) {
  Mac m = Mac::MakeRandom();
  std::string val = m.Hex();
  EXPECT_TRUE(val.size() <= 17);
  EXPECT_TRUE(val.size() >= 11);
}

TEST(Mac, test_mac_from_stream) {
  std::string exp = "be:d0:74:fe:87:64";
  std::stringstream ss;
  ss << exp;
  Mac m;
  Mac::FromStream(ss, m);
  EXPECT_EQ(exp, m.Hex());
}

TEST(IPv4, test_ip) {
  IPv4 ip("192.168.0.1");
  std::cout << ip.GetAddress() << std::endl;
  EXPECT_EQ(ip.GetAddress(), 0x0100a8c0);
  std::string ipdot("192.168.0.1");
  EXPECT_EQ(ip.GetDotAddress(), ipdot);
}

TEST(Subnet, test_all) {
  Subnet sn("11.1.1.3", 24);
  EXPECT_STREQ("11.1.1.3/24", sn.GetDotSubnetAddress().c_str());
  EXPECT_STREQ("255.255.255.0", sn.GetDotSubnetMask().c_str());
  EXPECT_EQ(0x00FFFFFF, sn.GetSubnetMask());
  EXPECT_EQ(0x0001010B, sn.GetNetworkId());
  EXPECT_STREQ("11.1.1.0", sn.GetDotNetworkId().c_str());
  EXPECT_EQ(0xFF000000, sn.GetBroadcastAddress());
  EXPECT_STREQ("0.0.0.255", sn.GetDotBroadcastAddress().c_str());
  EXPECT_EQ(254, sn.GetMaxNumberOfAddresses());
}
