#include "application.hpp"

#include <iostream>

application::application(std::span<std::string_view const> const args)
: _renderer(args)
{
}

void application::run()
{
}