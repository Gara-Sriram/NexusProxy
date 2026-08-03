#include "Logger.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <thread>

std::mutex Logger::logMutex;

namespace
{
    std::string getCurrentTime()
    {
        auto now = std::chrono::system_clock::now();

        std::time_t currentTime =
            std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;

        ss << std::put_time(
                std::localtime(&currentTime),
                "%Y-%m-%d %H:%M:%S"
             );

        return ss.str();
    }
}

void Logger::info(const std::string& message)
{
    std::lock_guard<std::mutex> lock(logMutex);

    std::cout
        << "["
        << getCurrentTime()
        << "] "

        << "[INFO] "

        << "[Thread "
        << std::this_thread::get_id()
        << "] "

        << message

        << std::endl;
}

void Logger::error(const std::string& message)
{
    std::lock_guard<std::mutex> lock(logMutex);

    std::cerr
        << "["
        << getCurrentTime()
        << "] "

        << "[ERROR] "

        << "[Thread "
        << std::this_thread::get_id()
        << "] "

        << message

        << std::endl;
}