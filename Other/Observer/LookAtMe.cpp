#include "LookAtMe.hpp"
#include "Observer.hpp"

void LookAtMe::subNewObserver(
    const std::shared_ptr<Observer>& sh_ptr_observer) {
    observers.emplace_back(sh_ptr_observer);
}

void LookAtMe::changeSelf() {
    for (auto it = observers.begin(); it != observers.end();) {
        auto sh_ptr_o = it->lock();

        if (!sh_ptr_o) {
            it = observers.erase(it);
        } else {
            sh_ptr_o->notify();
            ++it;
        }
    }
}
