#include <exception>
#include <iostream>
#include <span>
#include <stdexcept>
#include <string_view>
#include <vulkan/wrappers.hpp>

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
  }
  catch(std::exception &error)
  {
    std::cerr << error.what();
    return EXIT_FAILURE;
  }
  catch(...)
  {
    std::cerr << "unknown error";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
