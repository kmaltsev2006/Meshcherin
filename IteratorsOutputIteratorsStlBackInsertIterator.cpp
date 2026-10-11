#include "common.hpp"

#include <vector>
#include <iterator>
#include <algorithm>

int main() {
  std::vector<int> a;
  std::generate_n(std::back_insert_iterator(a), 10, [n = 0] mutable {return ++n;});

  for_each(a.cbegin(), a.cend(), [](const auto& el){std::print("{} ", el);});
  std::print("\n");

  std::vector<int> b;
  std::copy_if(a.cbegin(), a.cend(), std::back_inserter(b), [](const auto& el){return el % 2 == 0;});
  for_each(b.cbegin(), b.cend(), [](const auto& el){std::print("{} ", el);});
  std::print("\n");
}