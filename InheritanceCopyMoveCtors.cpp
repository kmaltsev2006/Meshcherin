/**
 * @brief Copy and Move ctors are NOT inherited at all
 * 
 * Without diminishing the generality: let's consider CopyCtor:
 * 
 * Compiler defined (default) CopyCtor looks like this:
 * Derived(const Derived& rhs)
 *     : Base(rhs) // implicit cast Derived& -> Base&
 * {}
 *
 * So if user defined CopyCtor WITHOUT explicitly calling Base CopyCtor
 * it won't be called -> possible UB
 */

#include "common.hpp"

struct Granny {
    Granny() = default;
    Granny(const Granny&) { PRINT_CALL(); }
};

struct Mom : Granny {
    Mom() = default;
    Mom(const Mom&) { PRINT_CALL(); }
};

// Has explicit CopyCtor
struct Son : Mom {
    Son() = default;
    Son(const Son& rhs) : x{rhs.x} { PRINT_CALL(); }

    int x{42};
};

// Has no explicit CopyCtor
struct Daughter : Mom {

    int x{42};
};

int main() {
    std::cout << "//CopyCtor behavior when explicitly defined//" << std::endl;
    Son s0;
    s0.x = 17;

    Son s1 {s0};
    // Son::Son(const Daughter&) -X-> Mom::Mom(const Mom&)
    std::cout << s1.x << std::endl; // 17 bc Son CopyCtor is called
    std::cout << std::endl;

    
    std::cout << "//CopyCtor behavior when NO explicitly defined//" << std::endl;
    Daughter d0;
    d0.x = 17;

    Daughter d1 {d0};
    // default Daughter::Daughter(const Daughter&) ---> Mom::Mom(const Mom&) -X-> Granny::Granny(const Granny&)
    std::cout << d1.x << std::endl; // 17 bc Daughter default CopyCtor is called and then Mom CopyCtor is called
}