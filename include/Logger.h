#pragma once

#include <string>
#include <mutex>

class Logger
{
private:
    static std::mutex logMutex;

public:
    static void info(const std::string& message);

    static void error(const std::string& message);
};