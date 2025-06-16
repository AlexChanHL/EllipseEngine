#pragma once

#include "Core/Base.hpp"
#include "Core/Formatter.hpp"

#include "sglLogger/Logger.hpp"


namespace Ellipse
{

class Log
{
    public:
     Log();
     ~Log();

     static void init();

     static SharedPtr<sglLogger::Logger> logger(String name);

    private:
     static Map<String, SharedPtr<sglLogger::Logger>> m_loggers;
};

std::ostream& operator<<(std::ostream& os, Mat4 mat);


}    // Ellipse


#define ELLIPSE_APP_LOG_TRACE(...) Ellipse::Log::logger("App")->traceLog(sglLogger::SourceData(__FILE__, __LINE__), __VA_ARGS__)
#define ELLIPSE_ENGINE_LOG_TRACE(...) Ellipse::Log::logger("Engine")->traceLog(sglLogger::SourceData(__FILE__, __LINE__), __VA_ARGS__)

#define ELLIPSE_APP_LOG_DEBUG(...) Ellipse::Log::logger("App")->debugLog(sglLogger::SourceData(__FILE__, __LINE__), __VA_ARGS__)
#define ELLIPSE_ENGINE_LOG_DEBUG(...) Ellipse::Log::logger("Engine")->debugLog(sglLogger::SourceData(__FILE__, __LINE__), __VA_ARGS__)

#define ELLIPSE_APP_LOG_INFO(...) Ellipse::Log::logger("App")->infoLog(sglLogger::SourceData(__FILE__, __LINE__), __VA_ARGS__)
#define ELLIPSE_ENGINE_LOG_INFO(...) Ellipse::Log::logger("Engine")->infoLog(sglLogger::SourceData(__FILE__, __LINE__), __VA_ARGS__)

#define ELLIPSE_APP_LOG_WARN(...) Ellipse::Log::logger("App")->warnLog(sglLogger::SourceData(__FILE__, __LINE__), __VA_ARGS__)
#define ELLIPSE_ENGINE_LOG_WARN(...) Ellipse::Log::logger("Engine")->warnLog(sglLogger::SourceData(__FILE__, __LINE__), __VA_ARGS__)

#define ELLIPSE_APP_LOG_ERROR(...) Ellipse::Log::logger("App")->errorLog(sglLogger::SourceData(__FILE__, __LINE__), __VA_ARGS__)
#define ELLIPSE_ENGINE_LOG_ERROR(...) Ellipse::Log::logger("Engine")->errorLog(sglLogger::SourceData(__FILE__, __LINE__), __VA_ARGS__)

#define ELLIPSE_APP_LOG_SERVERE(...) Ellipse::Log::logger("App")->servereLog(sglLogger::SourceData(__FILE__, __LINE__), __VA_ARGS__)
#define ELLIPSE_ENGINE_LOG_SERVERE(...) Ellipse::Log::logger("Engine")->servereLog(sglLogger::SourceData(__FILE__, __LINE__), __VA_ARGS__)

