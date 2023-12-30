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
    application(args).run();
  }
  catch(std::exception &error)
  {
    application::log::error << error.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
