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

struct Son : virtual Mom, virtual Dad {
// static void* svptr (holds address in .data memory)
    uint64_t s {0xDDDDDDDDDDDDDDDD};
}; // |F0EC8D6D.EA580000|DDDDDDDD.DDDDDDDD|AAAAAAAA.AAAAAAAA|BBBBBBBB.BBBBBBBB|AAAAAAAA.AAAAAAAA|CCCCCCCC.CCCCCCCC|
   // |svptr                     Son      |        Granny   -        Mom      |        Granny   -        Dad      |

int main() {
    printInfo<Son>(); // svptr is the same for all instances
    printInfo<Son>(); // svptr is the same for all instances
    printInfo<Son>(); // svptr is the same for all instances
}