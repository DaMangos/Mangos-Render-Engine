

#include "graphics/pixel.hpp"
#include "graphics/render_window.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <system_error>

int main()
{
  try
  {
    std::filesystem::create_directory("log");

    std::ofstream error_out("log/error.log", std::ios_base::out | std::ios_base::trunc);
    std::ofstream warning_out("log/warning.log", std::ios_base::out | std::ios_base::trunc);
    std::ofstream info_out("log/info.log", std::ios_base::out | std::ios_base::trunc);
    std::ofstream verbose_out("log/verbose.log", std::ios_base::out | std::ios_base::trunc);

    graphics::render_window::error_out.rdbuf(error_out.rdbuf());
    graphics::render_window::warning_out.rdbuf(warning_out.rdbuf());
    graphics::render_window::info_out.rdbuf(info_out.rdbuf());
    graphics::render_window::verbose_out.rdbuf(verbose_out.rdbuf());

    using namespace graphics::pixel_literals;

    graphics::render_window window("Hello, World!", 800_px, 600_px);

    return 0;
  }
  catch(std::system_error const & e)
  {
    std::cerr << "\033[1m\033[31merror:\033[0m\033[1m " << e.what();
    std::cerr << ", \033[1m\033[33mcategory:\033[0m\033[1m " << e.code().category().name();
    std::cerr << ", \033[1m\033[35mvalue:\033[0m\033[1m " << e.code().value() << std::endl;
  }
  catch(std::exception const & e)
  {
    std::cerr << "\033[1m\033[31merror:\033[0m\033[1m " << e.what() << std::endl;
  }
  catch(...)
  {
    std::cerr << "\033[1m\033[31merror:\033[0m\033[1m Unknown exception" << std::endl;
  }
}
