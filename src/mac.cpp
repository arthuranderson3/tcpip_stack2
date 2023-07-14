#include "mac.h"
#include <cstring>
#include <random>
#include <sstream>
#include <string>

Mac Mac::MakeRandom() {
  std::random_device rd;  // a seed source for the random number engine
  std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<uint32_t> distrib(0, 0xFF);

  Mac m;
  for (int i = 0; i < 6; i++) {
    uint32_t v = distrib(gen);
    m.addr[i] = v;
  }
  return m;
}

std::string Mac::Hex() const {
  std::stringstream ss;
  for (int i = 0; i < 6; i++) {
    uint16_t v = addr[i];
    ss << std::hex << v;
    if (i == 5) {
      continue;
    }
    ss << ':';
  }
  return ss.str();
}

std::istream &Mac::FromStream(std::istream &is, Mac &m) {
  int idx = 0;
  std::string hex_str;
  std::getline(is, hex_str);
  uint32_t size = hex_str.size();
  char str_buf[size + 1];
  ::memcpy(str_buf, hex_str.c_str(), size);
  str_buf[size + 1] = '\0';

  char *str = str_buf;
  char *token = strsep(&str, ":");
  do {
    char *end;
    int16_t v = strtol(token, &end, 16);
    m.addr[idx++] = v;
  } while ((token = strsep(&str, ":")) != nullptr);

  return is;
}
