#pragma once

namespace dwhbll::network::http {
    enum class HTTP_METHOD {
        CONNECT = 0,
        DELETE = 1,
        GET = 2,
        HEAD = 3,
        OPTIONS = 4,
        PATCH = 5,
        POST = 6,
        PUT = 7,
        TRACE = 8,
    };
}
