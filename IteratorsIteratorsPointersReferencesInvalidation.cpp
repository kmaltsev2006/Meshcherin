#include "common.hpp"

#include <vector>

int main() {
  std::vector<int> v {0, 1, 2};

  auto it = v.begin() + 2;
  auto* p = &v[2];
  auto& r = v[2];


  v.push_back(3); // it, p and r become invalidated
  
  /*
  BTW: not in every data structure all three become invalidated simultaneously,
  i.e. in std::deque push_back/push_front invalidate only iterators, but not pointers
  and references
  */

  std::print("{}\n", *it); // UB
  std::print("{}\n", *p); // UB
  std::print("{}\n", r); // UB
}