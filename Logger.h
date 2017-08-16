#ifndef LOGGER_H
#define LOGGER_H

#include <functional>
#include <sstream>

namespace logging {

class Logger {
public:
    enum LogLevel {
        Trace, Debug, Info, Warn, Error, Fatal, ENUM_LEVEL_NUM
    };

    using OutputCallback = std::function<void (std::string)>;

public:
    Logger(const char* filename, int line, const char* func_name, LogLevel);
    ~Logger();

    std::stringstream& stream();

    static LogLevel logLevel();
    static void setLevel(LogLevel level);
    static void setOutput(OutputCallback cb);

private:
    std::stringstream sstream_;
    static LogLevel level_limit_;
    static OutputCallback output_callback_;
};

}

#define LOG_TRACE if (logging::Logger::logLevel() <= logging::Logger::Trace) \
    logging::Logger(__FILE__, __LINE__, __func__,logging::Logger::Trace).stream()

#define LOG_DEBUG if (logging::Logger::logLevel() <= logging::Logger::Debug) \
    logging::Logger(__FILE__, __LINE__, __func__, logging::Logger::Debug).stream()

#define LOG_INFO if (logging::Logger::logLevel() <= logging::Logger::Info) \
    logging::Logger(__FILE__, __LINE__, __func__, logging::Logger::Info).stream()

#define LOG_WARN logging::Logger(__FILE__, __LINE__, __func__, logging::Logger::Warn).stream()

#define LOG_ERROR logging::Logger(__FILE__, __LINE__, __func__, logging::Logger::Error).stream()

#define LOG_FATAL logging::Logger(__FILE__, __LINE__, __func__, logging::Logger::Fatal).stream()

#endif
