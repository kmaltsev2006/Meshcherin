#include "common.hpp"

struct Granny {
    uint64_t g {0xAAAAAAAAAAAAAAAA};
};

struct Dad : Granny {
    uint64_t d {0xCCCCCCCCCCCCCCCC};
};

struct Son : Dad, Granny {
    uint64_t s {0xDDDDDDDDDDDDDDDD};
}; // |AAAAAAAA.AAAAAAAA|CCCCCCCC.CCCCCCCC|AAAAAAAA.AAAAAAAA|DDDDDDDD.DDDDDDDD|
//                                        |  unaccessible   |

int main() {
    Son s;

    printBytes(s);
    // s.g = 0x0; // error: request for member ‘g’ is ambiguous
    s.Dad::g;

    s.Dad::g = 0x0;
    printBytes(s);
}