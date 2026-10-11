/**
 * @brief const_cast<PtrType> - use to modify cv-qualifiers
 *
 * Use ONLY in case shown bellow: to remove const from a ref or ptr
 * when the underlying object is known to be non-const or mutable,
 * otherwise UB
 *
 * const_cast also can add const quilifeier, but using static_cast for this is
 * preferable
 */
#include "../common.hpp"

void foo(const int& x_ref) { const_cast<int&>(x_ref) = 17; }

int main() {
    int x{42};
    foo(x);
    std::cout << x << std::endl;
}