#include "common.hpp"

template<typename T>
class Vector {
public:
  Vector() = delete;
};

template<>
class Vector<bool> {
  struct BitReference {
  public:
    explicit BitReference(uint8_t* cell, uint8_t offset)
      : _cell{cell}
      , _offset{offset}
    {}

    void operator=(const bool value) {
      if (value) {
        *_cell |= (1 << _offset);
      } else {
        *_cell &= ~(1 << _offset);
      }
    }

    operator bool() {
      return static_cast<bool>(*_cell & (1 << _offset));
    }

  private:
    uint8_t* _cell;
    uint8_t _offset;
};

public:
  Vector(const size_t size)
    : _buf {new uint8_t[size / 8]{}}
    , _sz {size}
  {}

  ~Vector() {
    delete[] _buf;
  }

  BitReference operator[](const size_t i) {
    return BitReference{_buf + i / 8, static_cast<uint8_t>(i % 8)};
  }

private:
  uint8_t* _buf {nullptr};
  size_t _sz {0};
  size_t _cap {0};
};

int main() {
  constexpr size_t size {17};
  Vector<bool> b(size);
  for (size_t i = 0; i < size; i += 3) {
    b[i] = true;
  }
  for (size_t i = 0; i < size; ++i) {
    std::print("{} ", static_cast<bool>(b[i]));
  }
  std::print("\n");
}