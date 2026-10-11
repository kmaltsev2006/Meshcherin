/**
 * InputIterator has only pre-increment operator, because by seamantics it is unipass,
 * so we must not have such operator that will return "previous" value of iterator
 * 
 * Also interesting part is that InputIterator constructed by default is used as
 * end of isstream
 */

#include "common.hpp"

#include <iterator>
#include <vector>
#include <algorithm>

template<typename T>
class IstreamIterator {
public:
  using difference_type = size_t;
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using iterator_category = std::input_iterator_tag;

  IstreamIterator() = default;

  IstreamIterator(std::istream& is)
    : _is_ptr {&is}
  {
    is >> value;
  }

  IstreamIterator& operator++() {
    if (!(*_is_ptr >> value)) {
      *this = IstreamIterator();
    }
    return *this;
  }

  bool operator!=(const IstreamIterator& rhs) {
    return _is_ptr != rhs._is_ptr;
  }

  T& operator*() {
    return value;
  }

private:
  std::istream* _is_ptr {nullptr};
  T value;
};

int main() {
  /*
  {
    IstreamIterator<int> iit{std::cin};
    std::vector<int> v;
    for (size_t i = 0; i < 5; ++i, ++iit) {
      v.push_back(*iit);
    }
    for_each(v.cbegin(), v.cend(), [](const auto& el){std::print("{} ", el);});
    std::print("\n");
  }
  */

  {
    IstreamIterator<int> iit{std::cin};
    std::vector<int> v;
    std::copy(iit, IstreamIterator<int>{}, std::back_inserter(v));
    for_each(v.cbegin(), v.cend(), [](const auto& el){std::print("{} ", el);});
    std::print("\n");
  }
}