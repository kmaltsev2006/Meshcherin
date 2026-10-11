#include "common.hpp"

struct Granny {
    uint64_t g {0xAAAAAAAAAAAAAAAA};
};

struct Mom : virtual Granny {
// static void* msvptr (holds address in .data memory)
    uint64_t m {0xBBBBBBBBBBBBBBBB};
};
struct Dad : virtual Granny {
// static void* dsvptr (holds address in .data memory)
    uint64_t d {0xCCCCCCCCCCCCCCCC};
};

struct Son : Mom, Dad {
// static void* Mom::msvptr (son uses Mom's msvptr as his own, but with different value bc Mom's start address and Son's start address are the same)
// static void* Dad::dsvptr
    uint64_t s {0xDDDDDDDDDDDDDDDD};
}; // |781C877F.40640000|BBBBBBBB.BBBBBBBB|901C877F.40640000|CCCCCCCC.CCCCCCCC|DDDDDDDD.DDDDDDDD|AAAAAAAA.AAAAAAAA|
//    |msvptr                    Mom      |dsvptr                    Dad      |        Son      |        Granny   |                              

int main() {
    Son son;
    printBytes(son); // |781C877F.40640000|BBBBBBBB.BBBBBBBB|901C877F.40640000|CCCCCCCC.CCCCCCCC|DDDDDDDD.DDDDDDDD|AAAAAAAA.AAAAAAAA|
    son.g = 0x0; // OK (not ambiguous)
    printBytes(son); // |781C877F.40640000|BBBBBBBB.BBBBBBBB|901C877F.40640000|CCCCCCCC.CCCCCCCC|DDDDDDDD.DDDDDDDD|00000000.00000000|

    printBytes(static_cast<Dad&>(son));

    
    /*
        vtable holds numbers:
        v_offset[i] - offset to virtual base[i]
        top_offset  - offset of This class in Derived class

        for msvtable:
        v_offset = [40]
        top_offset = 0

        for dsvtable:
        v_offset = [24]
        top_offset = -16

        This allows down casts from This to Derived and upper casts from This to virtual Base
    */

    std::cout << std::endl;
    printBytes(static_cast<Son&>(static_cast<Mom&>(son)));
    printBytes(static_cast<Granny&>(static_cast<Mom&>(son)));
    printBytes(static_cast<Son&>(static_cast<Dad&>(son)));
    printBytes(static_cast<Granny&>(static_cast<Dad&>(son)));
}