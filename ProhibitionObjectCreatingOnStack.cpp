#include "common.hpp"

#include <utility>

class OnlyOnHeap_1 {
public:
  ~OnlyOnHeap_1() { PRINT_CALL(); }

  template<typename... Args>
  static OnlyOnHeap_1* create(Args&&... args) {
    return new OnlyOnHeap_1{std::forward<Args>(args)...};
  }
private:
  OnlyOnHeap_1() = default;
};

class OnlyOnHeap_2 {
public:
  static void operator delete(OnlyOnHeap_2* ptr, std::destroying_delete_t) {
    ptr->~OnlyOnHeap_2();
    ::operator delete(ptr);
  }

private:
  ~OnlyOnHeap_2() { PRINT_CALL(); }
};

int main() {
  {
    // OnlyOnHeap_1 obj; // error: ‘constexpr OnlyOnHeap_1::OnlyOnHeap_1()’ is private within this context
    OnlyOnHeap_1* obj_ptr {OnlyOnHeap_1::create()};
    delete obj_ptr;
  }
  
  {
    // OnlyOnHeap_2 obj;
    OnlyOnHeap_2* obj_ptr {new OnlyOnHeap_2{}};
    delete obj_ptr;
  }
}