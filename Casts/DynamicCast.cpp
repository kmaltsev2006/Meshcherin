/**
 * @brief dynamic_cast<PtrType> - use for ptr and ref conversions in polymorphic
 * class hierarchy where source type is polymorphic
 *
 * BTW: for ptr conversion returns nullptr in case of failure
 * BTW: for ref conversion throws in case of failure
 */

#include "../common.hpp"

/*
 G
/ \
M D
\/
S
*/
struct Granny {
    void goo() { PRINT_CALL(); }
    virtual ~Granny() = 0;
};
Granny::~Granny() = default;

struct Mom : virtual Granny {
    void moo() { PRINT_CALL(); }
};
struct Dad : virtual Granny {
    void doo() { PRINT_CALL(); }
};
struct Son : Mom, Dad {
    void soo() { PRINT_CALL(); }
};

int main() {
    {
        Granny* G = new Son{};
        if (auto s_ptr = dynamic_cast<Son*>(G)) {
            s_ptr->soo();
        }
        delete G;
    }

    {
        Mom* M = new Son{};
        if (auto d_ptr = dynamic_cast<Dad*>(M)) {
            d_ptr->doo();
        }
        delete M;
    }
}