#pragma once

#include <coroutine>
#include <liburing/io_uring.h>

#include <dwhbll/concurrency/coroutine/cancellable_base.h>

namespace dwhbll::concurrency::coroutine {
    /**
     * @brief an awaitable for the sole purpose of waiting for the associated uring completion.
     */
    class uring_promise : public cancellable_base {
        io_uring_cqe* cqe = nullptr;
        // todo get this into the reactor user_data struct instead.
        std::coroutine_handle<> waiter;

        friend class reactor;

    public:
        [[nodiscard]] bool await_ready() const noexcept;

        void await_suspend(std::coroutine_handle<> h) noexcept;

        [[nodiscard]] io_uring_cqe* await_resume() const;
    };
}
