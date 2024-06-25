#pragma once

#include "EllipsePCH.hpp"

namespace Utils
{

template<typename T>
std::string toString(const T& t)
{
   std::ostringstream os;
    os << t;
     return os.str();
}

}     //namespace utils
