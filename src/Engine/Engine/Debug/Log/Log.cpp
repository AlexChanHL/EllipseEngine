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

std::ostream& operator<<(std::ostream& os, glm::mat<4, 4, float>& mat4)
{
    for(int i=0;i<4;i++)
    {
    os << "Row: ";
    for(int j=0;j<4;j++)
    {
    os << mat4[j][i] << " , ";
    }
    os << "\n";
    }

  return os;
}
  
} // namespace Ellipse
