#include "Observer.hpp"
#include "LookAtMe.hpp"

size_t Observer::id{};

std::shared_ptr<Observer> Observer::create(LookAtMe& look_at_me) {
    auto sh_ptr_observer = std::shared_ptr<Observer>(new Observer{});
    look_at_me.subNewObserver(sh_ptr_observer);
    return sh_ptr_observer;
}

void Observer::notify() {
    std::cout << "Observer with id: " << _id << " been notified" << std::endl;
}

Observer::Observer() { _id = ++id; }
