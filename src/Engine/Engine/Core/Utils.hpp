#pragma once

#include "EllipsePCH.hpp"


namespace Ellipse
{

namespace Utils
{

template<typename T>
std::string toString(const T& t)
{
    std::ostringstream os;
    os << t;
    return os.str();
}

template<typename It>
It iteratorNext(It it, i64_t n)
{
     for(i64_t i=0;i<n;i++)
     {
     it++;
     }
   
     return it;
}

template<typename It, typename T>
i64_t indexAt(It begin, It end, T t)
{
     i64_t iterationCount = 0;
     for(auto it = begin; it != end; it++)
     {
     if(t == *it)
     {
     return iterationCount;
     }

     iterationCount++;
     }

     return iterationCount;
}

template<typename It, typename T, typename Func>
i64_t indexAt(It begin, It end, T t, Func func)
{
     i64_t iterationCount = 0;
     for(auto it = begin; it != end; it++)
     {
     if(t == *it)
     {
     return iterationCount;
     }

     iterationCount++;
     }

     return iterationCount;
}

template<typename T, typename D>
Vector<T> keyMap(Map<T, D> map)
{
     Vector<T> keys;
     for(auto it = map.begin(); it != map.end(); it++)
     {
     keys.push_back(it->first);
     }

     return keys;
}


}     // namespace Utils

}     // namespace Ellipse
