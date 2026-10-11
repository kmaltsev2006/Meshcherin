/**
 * alignof(Obj) == max(alignof(Obj::field1), alignof(Obj::field2), ...)
 */
#include "common.hpp"

struct alignas(4) AlignedPacket {
  uint8_t a;
  uint8_t b;
  uint8_t c;
};

struct Packet {
  uint8_t a;
  uint8_t b;
  uint8_t c;
};

int main() {
  {
    alignas(64) int x;
    std::print("alignof {}; sizeof {}\n", alignof(x), sizeof(x));
  }

  {
    AlignedPacket packet_arr[10];
    std::print("alignof {}; sizeof {}\n", alignof(*packet_arr), sizeof(packet_arr));
  }

  {
    Packet packet_arr[10];
    std::print("alignof {}; sizeof {}\n", alignof(*packet_arr), sizeof(packet_arr));
  }
}