#pragma once

#include <span>
#include <string_view>

struct render_engine final
{
    render_engine([[maybe_unused]] std::span<std::string_view const> const args);

    void run();

    render_engine(render_engine &&)                 = delete;
    render_engine(render_engine const &)            = delete;
    render_engine &operator=(render_engine &&)      = delete;
    render_engine &operator=(render_engine const &) = delete;
    ~render_engine()                                = default;
};