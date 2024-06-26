#include <mangos_render_engine/application.hpp>

#include <iostream>

int main(int const argc, char const * const * const argv) noexcept
{
  try
  {
    mangos_render_engine::application(std::vector<std::string_view>(argv, std::ranges::next(argv, argc))).run();
    return EXIT_SUCCESS;
  }
  catch(std::exception const & e)
  {
    std::cerr << "\033[1;31m" << "exception: " << "\033[0m" << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}