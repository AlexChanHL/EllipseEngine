
#include "Log.hpp"

#include "sglLogger/RouteMethod/RouteStdOut.hpp"


namespace Ellipse
{

Log::Log()
{

}
Map<String, SharedPtr<sglLogger::Logger>> Log::m_loggers = Map<String, SharedPtr<sglLogger::Logger>>();

Log::~Log()
{

}

void Log::init()
{
    m_loggers["Engine"] = createShared<sglLogger::Logger>();

    auto stdoutEngineRoute = createUnique<sglLogger::RouteStdOut>();

    m_loggers["Engine"]->setRootFile("/Users/alexchan_1/Project Files/C++/C++ ActiveProjects/EllipseEngine/");
    m_loggers["Engine"]->setRouteMethod(std::move(stdoutEngineRoute));
    m_loggers["Engine"]->setPattern("Engine: |$d| - $s - [ $f - $l ] [ $L ]");

    auto stdoutAppRoute = createUnique<sglLogger::RouteStdOut>();

    m_loggers["App"] = createShared<sglLogger::Logger>();

    m_loggers["App"]->setRootFile("/Users/alexchan_1/Project Files/C++/C++ ActiveProjects/EllipseEngine/");
    m_loggers["App"]->setRouteMethod(std::move(stdoutAppRoute));
    m_loggers["App"]->setPattern("App: $d $s $f $l $L");
}

SharedPtr<sglLogger::Logger> Log::logger(String name)
{
    return m_loggers[name];
}

std::ostream& operator<<(std::ostream& os, Mat4 mat)
{
    for(u64_t i=0;i<4;i++)
    {
    for(u64_t j=0;j<4;j++)
    {
    os << mat[j][i] << ' ';
    }
    os << '\n';
    }
    return os;
}

} // namespace Ellipse

