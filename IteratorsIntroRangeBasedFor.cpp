/**
 * Iterator categories:
 * InputIterator    OutputIterator
 *     |
 * ForwardIterator
 *     |
 * BidirectionalItrator
 *     |
 * RandomAccessIterator
 *     |
 * ContiguousIterator
 *
 * Main features of iterators:
 * 1) dereferencing
 * 2) incrementing
 * 3) comparison for equality
 */

#include "common.hpp"

#include <vector>
#include <algorithm>

int main() {
  std::vector<int> v (17);
  std::ranges::iota(v.begin(), v.end(), 0);

  // 1
  for (const auto& el : v) {
    /*  */
  }

  // 2
  decltype(v)::iterator it_begin = v.begin();
  decltype(v)::iterator it_end = v.end();
  for (; it_begin != it_end; ++it_begin) {
    /*  */
  }
}