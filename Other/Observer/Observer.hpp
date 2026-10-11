#pragma once

#include <cstddef>
#include <iostream>
#include <memory>

class LookAtMe;

class Observer {
  public:
    static std::shared_ptr<Observer> create(LookAtMe& look_at_me);

    void notify();

  private:
    Observer();

  private:
    size_t _id;
    static size_t id;
};
