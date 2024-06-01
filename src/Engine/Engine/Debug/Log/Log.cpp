#include "Log.hpp"

#include "uLogger/Sinks/StdoutSink.hpp"

namespace Ellipse
{
  std::shared_ptr<uLog::Logger> Log::m_clientLogger;
  std::shared_ptr<uLog::Logger> Log::m_engineLogger;

 void Log::init()
  {
  std::vector<std::shared_ptr<uLog::sinks::Sinks>> sinks;
   sinks.emplace_back(std::make_shared<uLog::sinks::stdout_basic_sink_mt>());
    
   m_clientLogger = std::make_shared<uLog::Logger>("AppLog",
                                                   sinks.begin(),
                                                   sinks.end());
    m_clientLogger->setLevel(uLog::Level::Trace);

   m_engineLogger = std::make_shared<uLog::Logger>("EngineLog",
                                                   sinks.begin(),
                                                   sinks.end());

    m_engineLogger->setLevel(uLog::Level::Trace);
  }
  
} // namespace Ellipse
