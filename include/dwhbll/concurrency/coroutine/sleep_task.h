#pragma once

#include <chrono>
#include <coroutine>

#include <dwhbll/concurrency/coroutine/cancellable_base.h>

namespace dwhbll::concurrency::coroutine {
    class sleep_task : public cancellable_base {
        std::chrono::steady_clock::time_point _finish;

    public:
        [[nodiscard]] explicit sleep_task(const std::chrono::steady_clock::time_point &finish)
            : _finish(finish) {
        }

        [[nodiscard]] bool await_ready() const noexcept;

        void await_suspend(std::coroutine_handle<> h) noexcept;

        void await_resume() const;
    };

    template <typename Dur>
    sleep_task sleep_for(Dur d) {
        return sleep_task{std::chrono::steady_clock::now() + d};
    }
}
