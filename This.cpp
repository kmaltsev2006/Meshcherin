#include "common.hpp"

#include <functional>

class MyClass {
  public:
    MyClass() : _id{_next_id++} {}

    void foo(std::string_view greeting) {
        PRINT_CALL();
        std::cout << this->_id << std::endl;
        std::cout << greeting << std::endl;
    }

  private:
    static size_t _next_id;
    size_t _id;
};
size_t MyClass::_next_id{};

int main() {
    MyClass a{};
    MyClass b{};

    std::invoke(&MyClass::foo, &a /* MyClass* this */,
                "hello from a" /*std::string_view greeting*/);
    std::invoke(&MyClass::foo, &b /* MyClass* this */,
                "hello from b" /*std::string_view greeting*/);
}