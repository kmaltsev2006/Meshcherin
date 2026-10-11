#include "common.hpp"

struct Mom {
    uint64_t m {0xAAAAAAAAAAAAAAAA};
}; // |AAAAAAAA.AAAAAAAA|
struct Dad {
    uint64_t d {0xBBBBBBBBBBBBBBBB};
}; // |BBBBBBBB.BBBBBBBB|
struct Son : Mom, Dad {
    uint64_t s {0xCCCCCCCCCCCCCCCC};
}; // |AAAAAAAA.AAAAAAAA|BBBBBBBB.BBBBBBBB|CCCCCCCC.CCCCCCCC|

int main() {
    printInfo<Mom>();
    printInfo<Dad>();
    printInfo<Son>();
}