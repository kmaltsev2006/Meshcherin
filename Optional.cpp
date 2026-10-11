#include "common.hpp"

class LifeTime {
public:
  LifeTime() { PRINT_CALL(); }
  LifeTime(const LifeTime&) { PRINT_CALL(); }
  LifeTime(LifeTime&&) { PRINT_CALL(); }
  ~LifeTime() { PRINT_CALL(); }
};

template<typename T>
struct Optional;

struct nullopt_t {
  template<typename T>
  operator Optional<T>() {
    PRINT_CALL();
    return Optional<T>{};
  }
};
nullopt_t nullopt;

template<typename T>
class Optional {
public:
  Optional() = default;

  explicit Optional(const T& obj)
    : _has_value {true}
  {
    new (_buf) T{obj};
  }

  ~Optional() {
    if (_has_value)
      std::bit_cast<T*>(static_cast<uint8_t*>(_buf))->~T();
  }

  bool operator==(nullopt_t) {
    return _has_value;
  }

  Optional& operator=(const T& obj) {
    new (_buf) T{obj};
    _has_value = true;
    return *this;
  }

  operator bool() const {
    return _has_value;
  }

  T& operator*() {
    return *std::bit_cast<T*>(static_cast<uint8_t*>(_buf));
  }

private:
  alignas(sizeof(T)) uint8_t _buf[sizeof(T)];
  bool _has_value {false};
};

Optional<LifeTime> foo(const int n) {
  if (n % 2 == 0) {
    return Optional(LifeTime{});
  }
  return nullopt;
}

int main() {
  {
    Optional<LifeTime> opt;
    std::print("{}\n", static_cast<bool>(opt));
    opt = LifeTime{};
    std::print("{}\n", static_cast<bool>(opt));
    std::print("{}\n", static_cast<void*>(&*opt));
  }

  std::print("\n");
  
  {
    auto o1 = foo(4);
    auto o2 = foo(5);
    std::print("{} {}\n", static_cast<bool>(o1), static_cast<bool>(o2));
  }
}