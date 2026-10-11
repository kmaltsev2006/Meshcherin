#include "common.hpp"

#include <iterator>
#include <type_traits>
#include <vector>
#include <list>

template<typename Iter>
auto distance(const Iter first, const Iter last) {
  PRINT_CALL();

  if constexpr (std::is_base_of_v<
    std::random_access_iterator_tag,
    typename std::iterator_traits<Iter>::iterator_category>) {
    
    return last - first;
  }

  typename std::iterator_traits<Iter>::difference_type dist{};
  for (auto it = first; it != last; ++it, ++dist) {}
  return dist;
}

int main() {
  std::vector<int> v(42);
  std::print("{}\n", ::distance(v.begin(), v.end()));
  
  std::list<int> l(42);
  std::print("{}\n", ::distance(l.begin(), l.end()));
}