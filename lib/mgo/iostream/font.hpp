#pragma once

namespace mgo
{
struct font
{
    static constexpr char const *const reset              = "\033[00m";
    static constexpr char const *const bold               = "\033[01m";
    static constexpr char const *const dark               = "\033[02m";
    static constexpr char const *const italic             = "\033[03m";
    static constexpr char const *const underline          = "\033[04m";
    static constexpr char const *const red                = "\033[31m";
    static constexpr char const *const green              = "\033[32m";
    static constexpr char const *const yellow             = "\033[33m";
    static constexpr char const *const blue               = "\033[34m";
    static constexpr char const *const magenta            = "\033[35m";
    static constexpr char const *const cyan               = "\033[36m";
    static constexpr char const *const white              = "\033[37m";
    static constexpr char const *const red_background     = "\043[31m";
    static constexpr char const *const green_background   = "\043[32m";
    static constexpr char const *const yellow_background  = "\043[33m";
    static constexpr char const *const blue_background    = "\043[34m";
    static constexpr char const *const magenta_background = "\043[35m";
    static constexpr char const *const cyan_background    = "\043[36m";
    static constexpr char const *const white_background   = "\043[37m";
};
}