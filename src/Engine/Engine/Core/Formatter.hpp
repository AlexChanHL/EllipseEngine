#pragma once

// #if USE_FMT

#include <fmt/format.h>

// #endif

namespace Ellipse
{

template<typename... Args>
using formatString = fmt::format_string<Args...>;

template<typename... Args>
String format(fmt::format_string<Args...> fmtString, Args&&... args)
{
    return fmt::format(fmt::runtime(fmtString), args...);
}

};    // namespace Ellipse

