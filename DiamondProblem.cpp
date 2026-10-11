#include "common.hpp"

struct Granny {
    uint64_t g {0xAAAAAAAAAAAAAAAA};
};

struct Mom : Granny {
    uint64_t m {0xBBBBBBBBBBBBBBBB};
};

struct Dad : Granny {
    uint64_t d {0xCCCCCCCCCCCCCCCC};
};

struct Son : Mom, Dad {
    uint64_t s {0xDDDDDDDDDDDDDDDD};
}; // |AAAAAAAA.AAAAAAAA|BBBBBBBB.BBBBBBBB|AAAAAAAA.AAAAAAAA|CCCCCCCC.CCCCCCCC|DDDDDDDD.DDDDDDDD|

int main() {
    printInfo<Son>();

    Son s;
    // s.g; // error: request for member ‘g’ is ambiguous
    s.Mom::g; // OK
    s.Dad::g; // OK

    // static_cast<Granny&>(s); // error: ‘Granny’ is an ambiguous base of ‘Son’
    static_cast<Granny&>(static_cast<Mom&>(s)); // OK
    static_cast<Granny&>(static_cast<Dad&>(s)); // OK
}