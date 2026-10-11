#include "common.hpp"

class Granny {
protected:
    void foo() { PRINT_CALL(); }
};

class Mom : private Granny {
friend class Son; // friends are not inherited

/*
private:                // Son access (because this is friend)
    protected:          // Son access
        Granny::foo();
*/
};

class Son : public Mom {
public:
    void bar() { PRINT_CALL(); foo(); }
};

int main() {
    Son{}.bar();
}