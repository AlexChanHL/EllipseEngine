#pragma once

#include "Core/Base.hpp"
#include "Core/Formatter.hpp"
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


#define ELLIPSE_APP_LOG_TRACE(...) std::cout << Ellipse::format(__VA_ARGS__) << '\n';
#define ELLIPSE_ENGINE_LOG_TRACE(...)std::cout << Ellipse::format(__VA_ARGS__) << '\n';

#define ELLIPSE_APP_LOG_DEBUG(...) std::cout << Ellipse::format(__VA_ARGS__) << '\n';
#define ELLIPSE_ENGINE_LOG_DEBUG(...) std::cout << Ellipse::format(__VA_ARGS__) << '\n';

#define ELLIPSE_APP_LOG_INFO(...) std::cout << Ellipse::format(__VA_ARGS__) << '\n';
#define ELLIPSE_ENGINE_LOG_INFO(...) std::cout << Ellipse::format(__VA_ARGS__) << '\n';

#define ELLIPSE_APP_LOG_WARN(...) std::cout << Ellipse::format(__VA_ARGS__) << '\n';
#define ELLIPSE_ENGINE_LOG_WARN(...) std::cout << Ellipse::format(__VA_ARGS__) << '\n';

#define ELLIPSE_APP_LOG_ERROR(...) std::cout << Ellipse::format(__VA_ARGS__) << '\n';
#define ELLIPSE_ENGINE_LOG_ERROR(...) std::cout << Ellipse::format(__VA_ARGS__) << '\n';

#define ELLIPSE_APP_LOG_FATAL(...) std::cout << Ellipse::format(__VA_ARGS__) << '\n';
#define ELLIPSE_ENGINE_LOG_FATAL(...) std::cout << Ellipse::format(__VA_ARGS__) << '\n';

