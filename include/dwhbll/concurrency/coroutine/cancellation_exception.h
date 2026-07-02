#pragma once

#include <stdexcept>

namespace dwhbll::concurrency::coroutine {
    class cancellation_exception : public std::runtime_error {
    public:
        cancellation_exception() : std::runtime_error("Job Cancelled") {}
    };
}
