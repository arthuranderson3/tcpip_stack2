#include <gtest/gtest.h>

#include "mac.h"
#include <cassert>
#include <iostream>
#include <sstream>

TEST(Mac, test_make_mac) {
  Mac m = Mac::MakeRandom();
  std::string val = m.Hex();
  EXPECT_TRUE(val.size() <= 17);
  EXPECT_TRUE(val.size() >= 11);
  std::cout << "test_make_mac " << val << std::endl;
}

TEST(Mac, test_mac_from_stream) {
  std::string exp = "be:d0:74:fe:87:64";
  std::stringstream ss;
  ss << exp;
  Mac m;
  Mac::FromStream(ss, m);
  EXPECT_EQ(exp, m.Hex());
}
