#include "common.hpp"

struct Base {
    uint32_t a {0xAAAAAAAA};
    uint8_t b {0xBB};
}; // |AAAAAAAA.BB------|
struct DerivedFirst : Base {
    uint64_t c {0xCCCCCCCCCCCCCCCC};
}; // |AAAAAAAA.BB------|CCCCCCCC.CCCCCCCC|

struct EmptyBase {
}; // |--
struct DerivedSecond : EmptyBase {
    uint64_t d {0xDDDDDDDDDDDDDDDD};
}; // |DDDDDDDD.DDDDDDDD|


int main() {
    printInfo<Base>();
    printInfo<DerivedFirst>();
    printInfo<EmptyBase>(); // sizeof(EmptyBase) == 1 bc its minimal size for object
    printInfo<DerivedSecond>(); // sizeof(DerivedSecond) == 8 bc of EBO
}