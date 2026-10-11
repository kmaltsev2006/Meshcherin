#include "common.hpp"

#include <list>
#include <memory_resource>

constexpr size_t kBytesCount {1024};
constexpr size_t kElementsNum {64};

int main() {
  std::array<std::byte, kBytesCount> buf;
  
  std::pmr::monotonic_buffer_resource mbr{buf.data(), sizeof(decltype(buf)::value_type) * buf.size()};
  std::pmr::polymorphic_allocator<int> alloc{&mbr};
  
  std::pmr::list<int> l {alloc};
  for (size_t i = 0; i < kElementsNum; ++i) {
    l.push_back(i);
  }
  std::pmr::list<int> r = l;
}
