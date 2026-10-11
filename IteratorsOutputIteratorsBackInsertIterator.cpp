#include "common.hpp"

#include <vector>
#include <algorithm>

template<typename Cont>
class BackInsertIterator {
public:
  explicit BackInsertIterator(Cont& cont)
    : _cont {cont}
  {}

  template<typename T>
  BackInsertIterator& operator=(const T& obj) {
    _cont.push_back(obj);
    return *this;
  }

  BackInsertIterator& operator*() {
    return *this;
  }

  BackInsertIterator& operator++() {
    return *this;
  }

  BackInsertIterator& operator++(int) {
    return *this;
  }

private:
  Cont& _cont;
};

template<typename Cont>
BackInsertIterator<Cont> backInserter(Cont& cont) {
  return BackInsertIterator(cont);
}

template<typename OutputIter>
OutputIter generateN(OutputIter it, const size_t count, auto gen) {
  for (size_t i = count; i > 0; --i, ++it) {
    *it = gen();
  }
  return it;
}

int main() {
  std::vector<int> v;
  auto it = generateN(backInserter(v), 10, [n=0] mutable {return ++n;});
  *it++ = 42;

  for_each(v.cbegin(), v.cend(), [](const auto& el){ std::print("{} ", el); });
  std::print("\n");
}