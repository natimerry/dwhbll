#pragma once

#include <coroutine>

#include <dwhbll/concurrency/coroutine/cancellable_base.h>

namespace dwhbll::concurrency::coroutine {
    class uring_sqe_awaitable : public cancellable_base {
    public:
        bool await_ready() noexcept;

        void await_suspend(std::coroutine_handle<> h) noexcept;

        void await_resume() noexcept;
    };

    uring_sqe_awaitable wait_for_sqe() noexcept;
}
