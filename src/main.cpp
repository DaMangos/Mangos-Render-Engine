#include "application.hpp"

#include <exception>
#include <iostream>
#include <vector>

int main(int const argc, char const *const *const argv)
{
  [[nodiscard]]
  int        better_main([[maybe_unused]] std::span<std::string_view const> const args) noexcept;
  auto const args = std::vector<std::string_view>(argv, std::ranges::next(argv, static_cast<std::ptrdiff_t const>(argc)));
  return better_main(args);
}

[[nodiscard]]
int better_main([[maybe_unused]] std::span<std::string_view const> const args) noexcept
{
  try
  {
    auto app = application(args);
    app.run();
  }
  catch(std::exception &error)
  {
    application::log::error << error.what();
    return EXIT_FAILURE;
  }
  catch(...)
  {
    application::log::error << "unknown exception";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
