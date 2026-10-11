#include "API.hpp"

#include <deque>
#include <iostream>
#include <set>
#include <vector>

class API::Impl {
  public:
    void foo() { std::cout << "foo" << std::endl; }

  private:
    std::vector<char> _v;
    std::deque<char> _d;
    std::set<char> _s;
};

API::API() : _p_impl{std::make_unique<Impl>()} {}

API::~API() = default;

API::API(const API& other) {
    if (other._p_impl) {
        _p_impl = std::make_unique<Impl>(*other._p_impl);
    }
}

API& API::operator=(const API& other) {
    if (this == &other)
        return *this;

    if (!other._p_impl)
        _p_impl.reset();
    else if (!_p_impl)
        _p_impl = std::make_unique<Impl>(*other._p_impl);
    else
        *_p_impl = *other._p_impl;

    return *this;
}

API::API(API&& other) = default;

API& API::operator=(API&& other) = default;

void API::foo() { _p_impl->foo(); }