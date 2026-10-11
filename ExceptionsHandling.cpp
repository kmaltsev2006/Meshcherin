/**
 * 1) Exceptions are catched by first catch wich fully matched type (or fully matched base class type)
 * 2) `throw ex_obj;` passes exception object by value and transfers control to the handler,
      so its better to catch by const reference
 * 3) Exceptions are also can be catched by base class type full match
 * 4) `thow;` passes exception object by reference catch(...) catches everything
 * 5) If excpetion is uncatched: std::terminate() -> std::abort() -> SIGABRT
 */
#include "common.hpp"

#include <exception>

void useCase1() {
  try {
    throw int{};
  } catch (long long) {
    std::print("Catched long long\n");
  } catch (int) {
    std::print("Catched int first\n");
  } catch (int) {
    std::print("Catched int first\n");
  }
}

void useCase2() {
  try {
    throw std::runtime_error{""};
  } catch (const std::runtime_error& e) {
    std::print("Catched std::runtime_error\n");
  }
}

void useCase3() {
  try {
    throw std::runtime_error{""};
  } catch (const std::exception& e) {
    std::print("Catched std::exception\n");
  }
}

void useCase4() {
  try {
    try {
      throw std::runtime_error{""};
    } catch (...) {
      throw;
    }
  } catch (const std::exception& e) {
    std::print("Catched std::exception\n");
  }
}

void useCase5() {
  try {
    throw std::runtime_error{""};
  } catch (const std::logic_error& e) {
    std::print("Catched std::logic_error\n");
  }
}

int main() {
  useCase1();
  useCase2();
  useCase3();
  useCase4();
  useCase5(); // std::terminate() -> std::abort() -> SIGABRT
}