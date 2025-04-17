#pragma once

#include "Core/Base.hpp"
// #include "uLogger/Logger.hpp"

namespace Ellipse
{

class Log
{
   public:
    static void init();

    // static SharedPtr<uLog::Logger>& clientLogger()
    // {
    // return m_clientLogger;
    // }
    // static SharedPtr<uLog::Logger>& engineLogger()
    // {
    // return m_engineLogger;
    // }

   private:
    // static SharedPtr<uLog::Logger> m_clientLogger;
    // static SharedPtr<uLog::Logger> m_engineLogger;
};

std::ostream& operator<<(std::ostream& os, glm::mat<4, 4, float>& mat4);

}    //Ellipse


#define ELLIPSE_APP_LOG_TRACE(...)
#define ELLIPSE_ENGINE_LOG_TRACE(...)

#define ELLIPSE_APP_LOG_DEBUG(...)
#define ELLIPSE_ENGINE_LOG_DEBUG(...)

#define ELLIPSE_APP_LOG_INFO(...)
#define ELLIPSE_ENGINE_LOG_INFO(...)

#define ELLIPSE_APP_LOG_WARN(...)
#define ELLIPSE_ENGINE_LOG_WARN(...)

#define ELLIPSE_APP_LOG_ERROR(...)
#define ELLIPSE_ENGINE_LOG_ERROR(...)

#define ELLIPSE_APP_LOG_FATAL(...)
#define ELLIPSE_ENGINE_LOG_FATAL(...)

