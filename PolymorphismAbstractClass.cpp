#include "common.hpp"

#include <utility>
#include <memory>

class Abstract {
public:
    Abstract()
        : _id {_next_id++}
    {}

    virtual ~Abstract() = 0;      // pure virtual
    virtual void foo() const = 0; // pure virtual

protected:
    size_t _id;

private:
    static size_t _next_id;
};
Abstract::~Abstract() = default;
size_t Abstract::_next_id {0};


class Derived : public Abstract {
public:
    Derived()
        : _data {new char{}}
    {}

    // Non-copiable
    Derived(const Derived&) = delete;
    Derived& operator=(const Derived&) = delete;

    Derived(Derived&& rhs)
        : Abstract(std::move(rhs))
        , _data{std::exchange(rhs._data, nullptr)}
    { PRINT_CALL(); }
    
    Derived& operator=(Derived&& rhs) {
        PRINT_CALL();
        if (this == &rhs) return *this;
        delete _data;
        Derived tmp {std::move(rhs)};
        _swap(tmp);
        return *this;
    }

    ~Derived() {
        delete _data;
    }

    void foo() const override {
        PRINT_CALL();
    }

    size_t getId() const {
        return _id;
    }

private:
    char* _data {nullptr};

private:
    void _swap(Derived& rhs) {
        std::swap(_data, rhs._data);
    }
};

int main() {
    Abstract* a1 {new Derived{}};
    Abstract* a2 {new Derived{}};
    Abstract* a3 {new Derived{std::move(*static_cast<Derived*>(a2))}};

    a1->foo();
    a2->foo();
    a3->foo();

    std::cout << dynamic_cast<Derived&>(*a1).getId() << std::endl;
    std::cout << dynamic_cast<Derived&>(*a2).getId() << std::endl;
    std::cout << dynamic_cast<Derived&>(*a3).getId() << std::endl;

    delete a1;
    delete a2;
    delete a3;

    // Abstract{}; // CE (can't create object of an abstract class)
}