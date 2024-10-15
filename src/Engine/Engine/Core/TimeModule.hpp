#pragma once
#include "Engine/Module.hpp"
#include "OSTime.hpp"
#include "Base.hpp"

namespace Ellipse
{

// [ Retrieving the time at mutiple instances, may differ in the
//   time ]
struct TimeModule : public ILayerModule
{
    public:
     TimeModule()
     : m_isPaused{false},
       m_pauseStart{0},
       m_difference{0}
     {
     setName("TimeModule");
     }

     virtual void initLayerModule() override
     {

     }

     virtual void onUpdateLayer() override
     {

     }
    
     void pause()
     {
     if(m_isPaused)
     {
     return;
     }

     m_isPaused = true;
     m_pauseStart = OSTime::secAndNSec();
     }

     void unPause()
     {
     if(!m_isPaused)
     {
     return;
     }

     m_isPaused = false;
     m_difference += OSTime::secAndNSec() - m_pauseStart;
     }

     bool setTimer(Timer& timer, int32_t val)
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

     int64_t sec() const
     {
     if(m_isPaused)
     {
     return int64_t(m_pauseStart - m_difference);
     }

     return int64_t(OSTime::secAndNSec() - m_difference);
     }

     // [ Nsec may be returning a wrong number ]
     int64_t nsec() const
     {
     if(m_isPaused)
     {
     // [ Weired casting, may lead to conversions to lower size types ] return int64_t((m_pauseStart - m_difference - double(int64_t(m_pauseStart - m_difference))) * pow(10, 9));
     }
     // [ Loses percision when dividing] 

     double difference = OSTime::secAndNSec() - m_difference;
     return int64_t((difference - double(int64_t(difference))) * pow(10, 9));
     }

     double secAndNSec() const
     {
     if(m_isPaused)
     {
     return m_pauseStart - m_difference;
     }
    
     return OSTime::secAndNSec() - m_difference;
     }

     bool isPaused() const
     {
     return m_isPaused;
     }

     static SharedPtr<TimeModule> createTimeModule()
     {
     return createShared<TimeModule>();
     }

    private:
     bool m_isPaused;
     double m_pauseStart;
     double m_difference;
};

}   // namespace Ellipse
