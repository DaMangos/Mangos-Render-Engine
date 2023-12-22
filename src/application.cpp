#include "application.hpp"

#include <iostream>

application::application([[maybe_unused]] std::span<std::string_view const> const args)
: _renderer(args)
{
}

void application::run()
{
}