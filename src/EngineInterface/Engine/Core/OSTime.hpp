#pragma once

#include "Core/Base.hpp"

namespace Ellipse
{

struct Timer
{
   public:
    Timer()
    : m_isSetTimer{true},
      m_secAndNSec{0}
    {
  
    }

   public:
    bool m_isSetTimer;
    double m_secAndNSec;
};

class OSTime
{
    public:
      OSTime() = default;
      ~OSTime() = default;

      static void init()
      {
      std::timespec ts;
      std::timespec_get(&ts, TIME_UTC);

      m_startTime = ts.tv_sec;
      }

      static bool setTimer(Timer& timer, const int32_t& val)
      {
      if(timer.m_isSetTimer)
      {
      timer.m_secAndNSec = secAndNSec();
      timer.m_isSetTimer = false;
      }

      if((secAndNSec() - timer.m_secAndNSec) >= val)
      {
      timer.m_isSetTimer = true;
      return true;
      }
      return false;
      }

      static int64_t sec()
      {
      std::timespec ts;
      std::timespec_get(&ts, TIME_UTC);

      return ts.tv_sec - m_startTime;
      }

      static int64_t nsec()
      {
      std::timespec ts;
      std::timespec_get(&ts, TIME_UTC);
      
      return ts.tv_nsec;
      }

      // [ Time may be returning a wrong time due to time taken until app time ]
      static double secAndNSec()
      {
      std::timespec ts;
      std::timespec_get(&ts, TIME_UTC);
      i64_t sec = ts.tv_sec - m_startTime;
      
      return double(sec) + (double(ts.tv_nsec) / pow(10, 9));
      }

    public:

    private:
      static int64_t m_startTime;
};

// int64_t OSTime::m_startTime = 0;

}    //   namespace Ellipse
