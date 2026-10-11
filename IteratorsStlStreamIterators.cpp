/**
 * std::istream_iterator is an example of InputIterator
 * (such iterator that can be used by unipass algorithms)
 *
 * std::ostream_iterator is an exmaple of OutputIterator
 */

#include "common.hpp"

#include <iterator>
#include <vector>
#include <algorithm>

int main() {
  std::istream_iterator<int> it {std::cin};

  std::vector<int> v;
  for (size_t i = 0; i < 5; ++i, ++it) {
    v.push_back(*it);
  }

  std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, "|"));
  std::print("\n");
  
  std::print("{}\n", typeid(typename std::iterator_traits<std::istream_iterator<int>>::iterator_category).name());
  std::print("{}\n", typeid(typename std::iterator_traits<std::ostream_iterator<int>>::iterator_category).name());
}