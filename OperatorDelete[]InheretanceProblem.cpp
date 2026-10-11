#include "common.hpp"

class Base {
public:
  Base()
    : _b{new char{0xAA}}
  {}
  virtual ~Base() = 0;
private:
  char* _b{nullptr};
};
Base::~Base() { /*PRINT_CALL();*/ delete _b; }

class Derived : public Base {
public:
  Derived()
    : _d{new char{0xBB}}
  {}

  ~Derived() { /*PRINT_CALL();*/ delete _d; }

private:
  char* _d{nullptr};

};
int main() {
  { // OK
    Base* base = new Derived{};
    delete base;

    /*
    dtor from vtable called
    
    mov     rax, qword ptr [rbp - 16]
    mov     qword ptr [rbp - 48], rax
    cmp     rax, 0
    je      .LBB2_3
    mov     rdi, qword ptr [rbp - 48]
    mov     rax, qword ptr [rdi]
    call    qword ptr [rax + 8]
    */
  }

  { // UB
    Base* base_arr = new Derived[4]{};
    delete[] base_arr; // UB
    /*
    Only Base dtor called (polymorphism mechanism not invoked)
    Moreover jump offset is incorrect (== sizeof(Base), when must be == sizeof(Derived))

    add     rdi, -16
    mov     qword ptr [rbp - 112], rdi
    call    Base::~Base() [complete object destructor]
    mov     rcx, qword ptr [rbp - 88]
    mov     rax, qword ptr [rbp - 112]
    cmp     rax, rcx
    mov     qword ptr [rbp - 96], rax
    jne     .LBB2_5
    */

    // delete[] static_cast<Derived*>(base_arr); // OK
  }
}