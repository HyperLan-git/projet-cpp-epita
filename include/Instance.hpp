#pragma once

#include <cstddef>

class Instance {
   public:
    Instance() = default;

    Instance(const Instance& copy) = delete;

    Instance& operator=(const Instance& copy) = delete;

    void* operator new[](size_t count) = delete;
    void operator delete[](void* ptr) = delete;
};