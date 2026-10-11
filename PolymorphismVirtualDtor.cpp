/**
 * @brief ALWAYS declare dtor of polymorphic Base as virtual 
 * 
 */

#include "common.hpp"

struct NonVirtualDtorBase {
    virtual void foo() {}
    ~NonVirtualDtorBase() { PRINT_CALL(); }
};
struct Derived1 : NonVirtualDtorBase {
    ~Derived1() { PRINT_CALL(); }
};

struct VirtualDtorBase {
    virtual void foo() {}
    virtual ~VirtualDtorBase() = 0; 
};
VirtualDtorBase::~VirtualDtorBase() { PRINT_CALL(); }
struct Derived2 : VirtualDtorBase {
    ~Derived2() { PRINT_CALL(); }
};

int main() {
    /*
    Called:
    NonVirtualDtorBase::~NonVirtualDtorBase()
    -> potential memory leak

    To delete object correctly via pointer (or reference) to its Base class
    we need to down cast back to Derived (so we will delete object via pointer (or reference) to Derived)
    to invoke inheritance chaining dtor mechanism
    */

    std::cout << "//No virtual dtor//" << std::endl;
    std::cout << "No down cast" << std::endl;
    delete static_cast<NonVirtualDtorBase*>(new Derived1{}); // Potential UB
    
    std::cout << "Down cast" << std::endl;
    delete static_cast<Derived1*>(
        static_cast<NonVirtualDtorBase*>(new Derived1{})
    ); // No UB

    std::cout << std::endl;

    /*
    Called:
    virtual Derived2::~Derived2();
    virtual VirtualDtorBase::~VirtualDtorBase()
    -> no memory leak

    Here we don't need to down cast to Derived to correctly delete object 
    */
    std::cout << "//Virtual dtor//" << std::endl;
    std::cout << "No down cast" << std::endl;
    delete static_cast<VirtualDtorBase*>(new Derived2{});
}