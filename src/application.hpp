#pragma once

#include "vulkan_engine.hpp"

struct application final
{
    application([[maybe_unused]] std::span<std::string_view const> const args);

    void run();

    application(application &&)                 = delete;
    application(application const &)            = delete;
    application &operator=(application &&)      = delete;
    application &operator=(application const &) = delete;
    ~application()                              = default;

  private:
    vulkan_engine _renderer;
};