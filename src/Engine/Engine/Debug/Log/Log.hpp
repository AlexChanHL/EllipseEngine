#pragma once

#include "Core/Base.hpp"
#include "uLogger/Logger.hpp"

namespace Ellipse
{

class Log
{
  public:
   static void init();

 static SharedPtr<uLog::Logger>& clientLogger() { return m_clientLogger; }
 static SharedPtr<uLog::Logger>& engineLogger() { return m_engineLogger; }

  private:
    static SharedPtr<uLog::Logger> m_clientLogger;
    static SharedPtr<uLog::Logger> m_engineLogger;
};

std::ostream& operator<<(std::ostream& os, glm::mat<4, 4, float>& mat4);

}    //Ellipse

  #ifndef DEACTIVE_LOGGING

 #if DEBUG

#define ELPSE_APP_LOG_TRACE(...)  Ellipse::Log::clientLogger()->trace(__VA_ARGS__)
#define ELPSE_ENGINE_LOG_TRACE(...)  Ellipse::Log::engineLogger()->trace(__VA_ARGS__)

#define ELPSE_APP_LOG_DEBUG(...) Ellipse::Log::clientLogger()->debug(__VA_ARGS__)
#define ELPSE_ENGINE_LOG_DEBUG(...) Ellipse::Log::engineLogger()->debug(__VA_ARGS__)

#else

#define ELPSE_APP_LOG_TRACE(...)
#define ELPSE_ENGINE_LOG_TRACE(...)

#define ELPSE_APP_LOG_DEBUG(...)
#define ELPSE_ENGINE_LOG_DEBUG(...)

 #endif // DEBUG

  #define ELPSE_APP_LOG_INFO(...) Ellipse::Log::clientLogger()->info(__VA_ARGS__)
  #define ELPSE_ENGINE_LOG_INFO(...) Ellipse::Log::engineLogger()->info(__VA_ARGS__)

  #define ELPSE_APP_LOG_WARN(...) Ellipse::Log::clientLogger()->warn(__VA_ARGS__)
  #define ELPSE_ENGINE_LOG_WARN(...) Ellipse::Log::engineLogger()->warn(__VA_ARGS__)

  #define ELPSE_APP_LOG_ERROR(...) Ellipse::Log::clientLogger()->error(__VA_ARGS__)
  #define ELPSE_ENGINE_LOG_ERROR(...) Ellipse::Log::engineLogger()->error(__VA_ARGS__)

  #define ELPSE_APP_LOG_FATAL(...) Ellipse::Log::clientLogger()->fatal(__VA_ARGS__)
  #define ELPSE_ENGINE_LOG_FATAL(...) Ellipse::Log::engineLogger()->fatal(__VA_ARGS__)

 #else

  #define ELPSE_APP_LOG_INFO(...)
  #define ELPSE_ENGINE_LOG_INFO(...)

  #define ELPSE_APP_LOG_WARN(...)
  #define ELPSE_ENGINE_LOG_WARN(...)

  #define ELPSE_APP_LOG_ERROR(...)
  #define ELPSE_ENGINE_LOG_ERROR(...)

  #define ELPSE_APP_LOG_FATAL(...)
  #define ELPSE_ENGINE_LOG_FATAL(...)

     #endif // DEACTIVE_LOGGING
