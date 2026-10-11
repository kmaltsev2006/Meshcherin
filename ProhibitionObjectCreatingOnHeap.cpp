#include "common.hpp"

class OnlyOnStack {
public:
  void* operator new(size_t count) = delete;
};

int main() {
  // OnlyOnStack* ptr_obj = new OnlyOnStack{}; // error: use of deleted function ‘static void* OnlyOnStack::operator new(size_t)’
  OnlyOnStack obj;
}