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

#define APP_LOG_TRACE(...)  Log::clientLogger()->trace(__VA_ARGS__)
#define ENGINE_LOG_TRACE(...)  Log::engineLogger()->trace(__VA_ARGS__)

#define APP_LOG_DEBUG(...) Log::clientLogger()->debug(__VA_ARGS__)
#define ENGINE_LOG_DEBUG(...) Log::engineLogger()->debug(__VA_ARGS__)

#else

#define APP_LOG_TRACE(...)
#define ENGINE_LOG_TRACE(...)

#define APP_LOG_DEBUG(...)
#define ENGINE_LOG_DEBUG(...)

 #endif // DEBUG

  #define APP_LOG_INFO(...) Log::clientLogger()->info(__VA_ARGS__)
  #define ENGINE_LOG_INFO(...) Log::engineLogger()->info(__VA_ARGS__)

  #define APP_LOG_WARN(...) Log::clientLogger()->warn(__VA_ARGS__)
  #define ENGINE_LOG_WARN(...) Log::engineLogger()->warn(__VA_ARGS__)

  #define APP_LOG_ERROR(...) Log::clientLogger()->error(__VA_ARGS__)
  #define ENGINE_LOG_ERROR(...) Log::engineLogger()->error(__VA_ARGS__)

  #define APP_LOG_FATAL(...) Log::clientLogger()->fatal(__VA_ARGS__)
  #define ENGINE_LOG_FATAL(...) Log::engineLogger()->fatal(__VA_ARGS__)

 #else

  #define APP_LOG_INFO(...)
  #define ENGINE_LOG_INFO(...)

  #define APP_LOG_WARN(...)
  #define ENGINE_LOG_WARN(...)

  #define APP_LOG_ERROR(...)
  #define ENGINE_LOG_ERROR(...)

  #define APP_LOG_FATAL(...)
  #define ENGINE_LOG_FATAL(...)

     #endif // DEACTIVE_LOGGING
