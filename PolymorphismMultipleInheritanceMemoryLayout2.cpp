#include "common.hpp"

struct Granny {
// static void* vptr;
    uint64_t a {0xAA};
    
    virtual ~Granny() = default;
};

struct Mom : virtual Granny {
// static void* Granny::vptr;
    uint64_t b {0xBB};
};

struct Dad : virtual Granny {
// static void* Granny::vptr;
    uint64_t c {0xCC};
};

struct Son : Mom, Dad {
// static void* Mom::Granny::vptr;
// static void* Dad::Granny::vptr;
// static void* Granny::vptr;
    uint64_t d {0xDD};
}; // |60EB51C5.3C570000|BB000000.00000000|88EB51C5.3C570000|CC000000.00000000|DD000000.00000000|B0EB51C5.3C570000|AA000000.00000000|

int main() {
    printInfo<Son>();
}