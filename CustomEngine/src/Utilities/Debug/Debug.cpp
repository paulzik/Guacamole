#include "Debug.h"
#include <iostream>
#include <ctime>

std::vector<LogEntry> Debug::logs;

std::string Debug::CurrentTimestamp()
{
    std::time_t now = std::time(nullptr);
    std::tm local{};
    localtime_s(&local, &now);

    char buffer[16];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", &local);
    return buffer;
}

void Debug::Log(const std::string& message)
{
    LogEntry log(LogLevel::Info, message, CurrentTimestamp());
    logs.push_back(log);
}

void Debug::LogWarning(const std::string& message)
{
    LogEntry warning(LogLevel::Warning, message, CurrentTimestamp());
    logs.push_back(warning);
}

void Debug::LogError(const std::string& message)
{
    LogEntry error(LogLevel::Error, message, CurrentTimestamp());
    logs.push_back(error);
}

const std::vector<LogEntry>& Debug::GetLogs()
{
    return logs;
}
