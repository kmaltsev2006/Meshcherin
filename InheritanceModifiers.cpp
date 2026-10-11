#include "common.hpp"

class Base {
    friend void friendlyFunctionCallBaz(const Base& a);
    friend struct FriendlyStruct;

  public:
    void foo() const {
        PRINT_CALL();
        bar();
    }

  private:
    void bar() const { PRINT_CALL(); }

  protected:
    void baz() const { PRINT_CALL(); }
};

class Derived : public Base {
  public:
    void qux() const { Base::baz(); }

  private:
    void baz() const { PRINT_CALL(); }

    void soos() const { PRINT_CALL(); }

    /* Inheritance intuition:
    public:                 // access
        public:             // access
            Base::foo();    
        private:            // no access
            Base::bar();
        protected:          // access
            Base::baz();
    */
};

void friendlyFunctionCallBaz(const Base& a) {
    PRINT_CALL();
    a.baz();
}

struct FriendlyStruct {
    void callABar(const Base& a) {
        PRINT_CALL();
        a.bar();
    }

    void callBBarAndSoos(const Derived& b) {
        PRINT_CALL();
        // If Derived would have Derived::bar() in private context:
        // shadowing will appear -> Derived::bar() will be chosen by most match rule -> CE
        b.bar(); // calls Base::bar() by most match rule

        // "Friends are not inherited":
        // b.soos(); // error: ‘void Derived::soos() const’ is private within this context
    }
};

int main() {
    Base a;
    a.foo();
    // a.bar(); // CE
    // a.baz(); // CE

    Derived b;
    b.foo();
    b.qux();
    // b.bar(); // CE
    // b.baz(); // CE

    friendlyFunctionCallBaz(a);
    friendlyFunctionCallBaz(b); // implicit cast to Base

    FriendlyStruct friendly;
    friendly.callABar(a);
    friendly.callBBarAndSoos(b);
}