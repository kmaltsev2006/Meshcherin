/**
 * @brief "Virtual diamond"
 * 
 * Virtual base classes are stored in memory in dfs traversal order from left to right
 */
#include "common.hpp"

struct Granny {
    uint64_t g {0xAAAAAAAAAAAAAAAA};
};
struct Mom : virtual Granny {
// static void* msvptr
    uint64_t m {0xBBBBBBBBBBBBBBBB};
};
struct Dad : virtual Granny {
// static void* dsvptr
    uint64_t d {0xCCCCCCCCCCCCCCCC};
};
struct Son : virtual Mom, virtual Dad {
// static void* Mom::msvptr (son uses Mom's msvptr as his own, but with different value, bc Mom's start address and Son's start address are the same)
// static void* Dad::dsvptr
    uint64_t s {0xDDDDDDDDDDDDDDDD};
}; // |50BC1D14.055C0000|DDDDDDDD.DDDDDDDD|68BC1D14.055C0000|BBBBBBBB.BBBBBBBB|AAAAAAAA.AAAAAAAA|80BC1D14.055C0000|CCCCCCCC.CCCCCCCC|
//    |pvptr                     Son      |msvptr                    Mom      |        Granny   |dsvtr                     Dad      |


/*
    void dfsFindOnlyVirtual(ClassName) {
        for (const auto& P : ClassName) {
            if (isVirtual(P)) {
                addToLayout(P);
                dfsFindOnlyVirtual(P);
            }
        }
    }
    
    dfsFindOnlyVirtual(Son): Mom, Granny, Dad
*/

int main() {
    // printInfo<Son>();
    Son son;
    printBytes(son);
    
    printBytes(static_cast<Mom&>(son), 16);
    printBytes(static_cast<Dad&>(son), 16);
    printBytes(static_cast<Granny&>(son));
}