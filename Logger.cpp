#include "Logger.h"
#include <iostream>
#include <ctime>
#include <utility>

namespace logging {

Logger::LogLevel DEFAULT_LEVEL = Logger::Trace;

typename Logger::LogLevel Logger::level_limit_ = DEFAULT_LEVEL;

typename Logger::OutputCallback Logger::output_callback_ = [](std::string msg) {
    std::cout << msg << std::endl;
};

const char* level_string[] = { "Trace", "Debug", "Info", "Warn", "Error", "Fatal" };

std::string getTimeStr()
{
    std::time_t t;
    std::time(&t);
    std::string str = std::ctime(&t);
    str.erase(str.size()-1);
    return str;
}

Logger::Logger(const char* filename, int line, const char* func_name, LogLevel level)
{
    setLevel(level);
    sstream_ << "[";
    sstream_ << level_string[level];
    sstream_ << "]";
    sstream_ << getTimeStr() << " ";
    sstream_ << filename << " ";
    sstream_ << "(" << line << ") ";
    sstream_ << func_name << " ";
    sstream_ << ": ";
}

Logger::Logger(const char* filename, int line, const char* func_name, bool to_abort)
    : Logger(filename, line, func_name, to_abort ? Fatal : Error)
{
}

Logger::~Logger()
{
    if (output_callback_) {
        std::string str = sstream_.str();
        sstream_.flush();
        output_callback_(std::move(str));
    }
    if (level_limit_ == Fatal) {
        sstream_.flush();
        ::abort();
    }
}

Logger::LogLevel Logger::logLevel()
{
    return Logger::level_limit_;
}

void Logger::setLevel(Logger::LogLevel level)
{
    Logger::level_limit_ = level;
}

void Logger::setOutput(OutputCallback cb)
{
    Logger::output_callback_ = std::move(cb);
}

std::stringstream& Logger::stream()
{
    return sstream_;
}

}
