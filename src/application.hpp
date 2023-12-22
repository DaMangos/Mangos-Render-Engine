#pragma once

#include "vulkan_engine.hpp"

#include <iostream>

struct application final
{
    application([[maybe_unused]] std::span<std::string_view const> const args);

    void run();

    struct log final
    {
      private:
        enum struct severity_level
        {
          warning,
          error,
          info
        };

        template <severity_level severity>
        struct ostream final
        {
            template <typename T>
            std::ostream &operator<<(T const &value) const
            {
              switch(severity)
              {
                case severity_level::warning :
                  return std::cerr << "[warning] " << value;
                case severity_level::error :
                  return std::cerr << "[error] " << value;
                case severity_level::info :
                  return std::cout << "[info] " << value;
              }
              return std::cout << value;
            }
        };

      public:
        static constexpr auto const warning = ostream<severity_level::warning>{};
        static constexpr auto const error   = ostream<severity_level::error>{};
        static constexpr auto const info    = ostream<severity_level::info>{};
    };

    application(application &&) = delete;

    application(application const &)            = delete;
    application &operator=(application &&)      = delete;
    application &operator=(application const &) = delete;
    ~application()                              = default;

  private:
    vulkan_engine _renderer;
};