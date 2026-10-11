#pragma once

#include <list>
#include <memory>

class Observer;

class LookAtMe {
  public:
    void subNewObserver(const std::shared_ptr<Observer>& sh_ptr_observer);

    void changeSelf();

  private:
    std::list<std::weak_ptr<Observer>> observers;
};
