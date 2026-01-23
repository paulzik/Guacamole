#include "Debug.h"
#include <iostream>

std::vector<LogEntry> Debug::logs;

void Debug::Log(const std::string& message)
{
    LogEntry log(LogLevel::Info, message);
    logs.push_back(log);
}

void Debug::LogWarning(const std::string& message)
{
    LogEntry warning(LogLevel::Warning, message);
    logs.push_back(warning);
}

void Debug::LogError(const std::string& message)
{
    LogEntry error(LogLevel::Error, message);
    logs.push_back(error);
}

const std::vector<LogEntry>& Debug::GetLogs()
{
    return logs;
}
