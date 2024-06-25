#pragma once

#include "uLogger/Logger.hpp"

namespace Ellipse
{

class Log
{
  public:
   static void init();

 static std::shared_ptr<uLog::Logger>& clientLogger() { return m_clientLogger; }
 static std::shared_ptr<uLog::Logger>& engineLogger() { return m_engineLogger; }

  private:
    static std::shared_ptr<uLog::Logger> m_clientLogger;
    static std::shared_ptr<uLog::Logger> m_engineLogger;
};

}    //Ellipse

  #ifndef DEACTIVE_LOGGING

 #if DEBUG

#define ELLIPSE_APP_LOG_TRACE(...)  Ellipse::Log::clientLogger()->trace(__VA_ARGS__)
#define ELLIPSE_ENGINE_LOG_TRACE(...)  Ellipse::Log::engineLogger()->trace(__VA_ARGS__)

#define ELLIPSE_APP_LOG_DEBUG(...) Ellipse::Log::clientLogger()->debug(__VA_ARGS__)
#define ELLIPSE_ENGINE_LOG_DEBUG(...) Ellipse::Log::engineLogger()->debug(__VA_ARGS__)

#else

#define ELLIPSE_APP_LOG_TRACE(...)
#define ELLIPSE_ENGINE_LOG_TRACE(...)

#define ELLIPSE_APP_LOG_DEBUG(...)
#define ELLIPSE_ENGINE_LOG_DEBUG(...)

 #endif // DEBUG

  #define ELLIPSE_APP_LOG_INFO(...) Ellipse::Log::clientLogger()->info(__VA_ARGS__)
  #define ELLIPSE_ENGINE_LOG_INFO(...) Ellipse::Log::engineLogger()->info(__VA_ARGS__)

  #define ELLIPSE_APP_LOG_WARN(...) Ellipse::Log::clientLogger()->warn(__VA_ARGS__)
  #define ELLIPSE_ENGINE_LOG_WARN(...) Ellipse::Log::engineLogger()->warn(__VA_ARGS__)

  #define ELLIPSE_APP_LOG_ERROR(...) Ellipse::Log::clientLogger()->error(__VA_ARGS__)
  #define ELLIPSE_ENGINE_LOG_ERROR(...) Ellipse::Log::engineLogger()->error(__VA_ARGS__)

  #define ELLIPSE_APP_LOG_FATAL(...) Ellipse::Log::clientLogger()->fatal(__VA_ARGS__)
  #define ELLIPSE_ENGINE_LOG_FATAL(...) Ellipse::Log::engineLogger()->fatal(__VA_ARGS__)

 #else

  #define ELLIPSE_APP_LOG_INFO(...)
  #define ELLIPSE_ENGINE_LOG_INFO(...)

  #define ELLIPSE_APP_LOG_WARN(...)
  #define ELLIPSE_ENGINE_LOG_WARN(...)

  #define ELLIPSE_APP_LOG_ERROR(...)
  #define ELLIPSE_ENGINE_LOG_ERROR(...)

  #define ELLIPSE_APP_LOG_FATAL(...)
  #define ELLIPSE_ENGINE_LOG_FATAL(...)

     #endif // DEACTIVE_LOGGING
