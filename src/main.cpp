#include <cstdlib>
#include <string_view>
#include <vector>

int main(int const argc, char const * const * const argv) noexcept
{
  try
  {
    std::vector<std::string_view> const args(argv, argv + argc);
    mangos_render_engine::application(args).run();
    return EXIT_SUCCESS;
  }
  catch(std::exception const & e)
  {
    return EXIT_FAILURE;
  }
}