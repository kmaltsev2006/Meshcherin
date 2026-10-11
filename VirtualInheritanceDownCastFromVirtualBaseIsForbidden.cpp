/**
 * @brief Down cast from virtual base is forbidden,
 * bc we don't know offset to left from current position
 *
 * Explanation:
 * 
       [ G ]
       /   \
    v /     \ v
   [ M ]   [ D ]
    /  \  /  \
   /    X    |
 [ Son ] [ Dau ]
    \       /
     \     /
     [ GS ]
 *
 * 1) Son memory layout:
 * [M][D][Son][G]
 *
 * 2) Daughter memory layout:
 * [M][D][Dau][G]
 *
 * 3) GS memory layout:
 * [M][D][Son][M][D][Dau][GS][G]
 *
 * If we try to cast G& -> Son& we should go to left like we are in case (1) or like we are in case (3)?
 * If we try to cast G& -> Dau& we should go to left like we are in case (2) or like we are in case (3)?
 * We don't know -> so cast is forbidden
 */

#include "common.hpp"

struct Base {
    uint64_t b {0xAA};
};

struct Derived : virtual Base {
    uint64_t d {0xBB};
}; // |307D25FB.F5630000|BB000000.00000000|AA000000.00000000|

int main() {
    printInfo<Derived>();

    Derived d;
    Base br {static_cast<Base&>(d)};

    // error: cannot convert from pointer to base class ‘Base’ to pointer to derived class ‘Derived’ because the base is virtual
    static_cast<Derived&>(br);
}