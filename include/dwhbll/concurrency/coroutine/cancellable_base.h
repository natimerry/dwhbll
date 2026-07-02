#pragma once

#include <coroutine>

namespace dwhbll::concurrency::coroutine {
    class cancellable_base {
        bool cancelled = false;

    public:
        void cancel() noexcept;

        [[nodiscard]] bool is_cancelled() const noexcept;

        [[nodiscard]] bool await_ready() const noexcept;

        void await_suspend(std::coroutine_handle<> h) const noexcept;

        void await_resume() const;
    };
}
