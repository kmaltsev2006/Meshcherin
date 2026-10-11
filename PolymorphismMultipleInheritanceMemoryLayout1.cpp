/**
 * @brief Thunk mechanism
 *
 * Dad::Granny::vptr points to vtable that has &Dad::thunk, where its defenition looks like this:
 *
    void Dad::thunk() {
        this += top_offset;
        Son::foo();
    }
    top_offset == -32
 *
 * Mechanism works similary to PointerAdjustment mechanism
 */

#include "common.hpp"

struct Granny {
// static void* vptr;
    uint64_t a {0xAA};
    
    virtual ~Granny() = default;
};

struct Mom : Granny {
// static void* Granny::vptr;
    uint64_t b {0xBB};
};

struct Dad : Granny {
// static void* Granny::vptr;
    uint64_t c {0xCC};
};

struct Son : Mom, Dad {
// static void* Mom::Granny::vptr;
// static void* Dad::Granny::vptr;
    uint64_t d {0xDD};
}; // |48EC9A5D.83580000|AA000000.00000000|BB000000.00000000|68EC9A5D.83580000|AA000000.00000000|CC000000.00000000|DD000000.00000000|

int main() {
    printInfo<Son>();
}