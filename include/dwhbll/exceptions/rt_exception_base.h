#pragma once

#include <format>
#include <stacktrace>
#include <stdexcept>

namespace dwhbll::exceptions {
    class rt_exception_base : public std::runtime_error {
#ifdef __cpp_lib_stacktrace
        std::stacktrace trace;
#endif

        void populate_trace();

    public:
        rt_exception_base() : std::runtime_error("") {
            populate_trace();
        }

        rt_exception_base(const rt_exception_base &other) = default;

        rt_exception_base(const std::string& what_arg) : std::runtime_error(what_arg) {
            populate_trace();
        }

        rt_exception_base(const char* what_arg) : std::runtime_error(what_arg) {
            populate_trace();
        }

        template <typename... Args>
        rt_exception_base(const std::string& fmt, Args&&... args) :
            std::runtime_error(std::vformat(fmt, std::make_format_args(args...))) {
            populate_trace();
        }

        [[nodiscard]] std::string get_prettyprint_trace() const;

        void trace_to_stderr() const;

        static void traceback_terminate_handler();
    };
}
