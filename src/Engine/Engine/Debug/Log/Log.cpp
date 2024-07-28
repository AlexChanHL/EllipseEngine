#include "Log.hpp"

#include "uLogger/Sinks/StdoutSink.hpp"

namespace Ellipse
{
   SharedPtr<uLog::Logger> Log::m_clientLogger;
   SharedPtr<uLog::Logger> Log::m_engineLogger;

 void Log::init()
  {
   Vector<SharedPtr<uLog::sinks::Sinks>> sinks;
   sinks.emplace_back(createShared<uLog::sinks::stdout_basic_sink_mt>());
    
   m_clientLogger = createShared<uLog::Logger>("AppLog",
                                                   sinks.begin(),
                                                   sinks.end());
   m_clientLogger->setLevel(uLog::Level::Trace);

   m_engineLogger = createShared<uLog::Logger>("EngineLog",
                                                   sinks.begin(),
                                                   sinks.end());

   m_engineLogger->setLevel(uLog::Level::Trace);
 }
  
} // namespace Ellipse
