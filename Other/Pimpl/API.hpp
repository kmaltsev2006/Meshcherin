#pragma once

#include <memory>

class API {
  public:
    API();
    ~API();

    API(const API& other);
    API& operator=(const API& other);

    API(API&& other);
    API& operator=(API&& other);

    void foo();

  private:
    class Impl; // forward declaration

  private:
    std::unique_ptr<Impl>
        _p_impl; // in some rare cases std::shared_ptr<Impl> can be used
};