#include "common.hpp"

#include <bitset>

struct Packet {
  uint8_t a : 3;
  uint8_t b : 5;
  uint8_t   : 4;
  uint8_t c : 2;
};

int main() {
  std::print("{}\n", sizeof(Packet));
  
  Packet p;
  p.c = 3;
  std::print("{}\n", static_cast<uint64_t>(p.c));
  p.c = 4; // overflow -> leads to p.c == 0
  std::print("{}\n", static_cast<uint64_t>(p.c));
}