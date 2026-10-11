#include "common.hpp"

struct Granny {
    uint64_t a {0xAA};
};
struct Mom : Granny {
// static void* vptr;
    uint64_t b {0xBB};
    virtual ~Mom() = default;
};
struct Son : Mom {
// static void* Mom::vptr;
    uint64_t c {0xCC};
}; // |D09C367C.FD580000|AA000000.00000000|BB000000.00000000|CC000000.00000000|
//                      |Granny           |
//    |Son                                                                    |

int main() {
    printInfo<Granny>();
    printInfo<Mom>();
    printInfo<Son>();

    Son s;
    printBytes(s);                       // Address: 0x7ffc16cbf4b0
    printBytes(static_cast<Granny&>(s)); // Address: 0x7ffc16cbf4b8

    // static_cast<Son&>(static_cast<Granny&>(s));
}