#pragma once
#include <string>
#include <vector>

enum class LogLevel
{
    Info,
    Warning,
    Error
};

struct LogEntry
{
    LogLevel level;
    std::string message;
};

class Debug{
public:
    static void Log(const std::string& message);
    static void LogWarning(const std::string& message);
    static void LogError(const std::string& message);

    static const std::vector<LogEntry>& GetLogs();
private:
    static std::vector<LogEntry> logs;
};