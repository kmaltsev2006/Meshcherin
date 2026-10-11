#include "common.hpp"

void* operator new(std::size_t count) {
  // throw std::bad_alloc{};
  return malloc(count);
}

struct Good {
  ~Good() { PRINT_CALL(); }
};

class Bad {
public:
  Bad() try 
    : _data {new char{}}
  {
    *_data = 42;
    throw std::runtime_error{"I am from Bad::Bad()"};
  }
  catch (const std::bad_alloc& e) {
    std::print("Something went wrong during Bad object construction, got bad_alloc exception. Nothing we can do...\n");
  } // exception is implicitly thrown forward after catch
  catch (const std::exception& e) {
    std::print("Something went wrong during Bad object construction, got exception\n");
    
    // Clear memory here if exception is NOT std::bad_alloc
    delete _data;
  } // exception is implicitly thrown forward after catch

  Bad(const Bad&) = delete;
  Bad(Bad&&) = delete;

  ~Bad() {
    PRINT_CALL();
    delete _data;
  }

private:
  char* _data{nullptr};
};


int main() {
  try {
    Good{};
    Bad{};
  } catch (const std::exception& e) {
    std::print("Got exception in main: \"{}\"\n", e.what());
  }

  // Good::~Good() is called, because object is fully constructed
  // Bad::~Bad() is NOT called, because object is ill formed
}