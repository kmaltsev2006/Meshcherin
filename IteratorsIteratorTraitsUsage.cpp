#include "common.hpp"

#include <iterator>
#include <vector>

template<typename Iterator>
auto getObj() {
  return typename std::iterator_traits<Iterator>::value_type {};
}

template<typename Iterator>
auto getCategory() {
  return typename std::iterator_traits<Iterator>::iterator_category {};
}

int main() {
  std::vector<int> v;
  printTypeNoCE(getObj<decltype(v)::iterator>());      // int
  printTypeNoCE(getCategory<decltype(v)::iterator>()); // random_access_iterator_tag
}