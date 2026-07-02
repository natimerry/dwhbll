#pragma once

#include <coroutine>
#include <dwhbll/concurrency/coroutine/cancellable_base.h>

namespace dwhbll::concurrency::coroutine {
    class defer_again_t : public cancellable_base {
    public:
        bool await_ready() const noexcept;

        void await_suspend(std::coroutine_handle<> h) noexcept;

        void await_resume() const noexcept;
    };

    namespace coro {
        /**
         * Reasoning for putting inside a smaller namespace:
         * - One should rarely want to use this, so it's inside a smaller
         * @return
         */
        defer_again_t defer();
    }
}
