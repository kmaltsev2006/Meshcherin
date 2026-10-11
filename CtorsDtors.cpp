#include "common.hpp"

struct ZeroTag {};

class MyClass {
  public:
    explicit MyClass(ZeroTag)
        : MyClass(0, 0)
    // , _useless_flag {false} // error: mem-initializer for
    // ‘MyClass::_useless_flag’ follows constructor delegation
    {}

    explicit MyClass(const int32_t x, const int32_t y) : _x{x}, _y{y} {}

  private:
    bool _useless_flag{true}; // default value is true
    int32_t _x;
    int32_t _y;
};

struct LilCoords {
    int32_t x{-1}; // default value is -1
    int32_t y{-1}; // default value is -1
};

int main() {
    MyClass{42, 17};     // Uniform initialization
    MyClass{ZeroTag{}};  // Uniform initialization via delegating constructor
    LilCoords{.y = -17}; // Designated initialization
    LilCoords{-42, -17}; // Aggregate intializtion
    LilCoords{-42};      // Aggregate intializtion
    LilCoords x{-42};    // Aggregate intializtion
}