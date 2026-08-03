#pragma once

#include <string>
#include <vector>
#include <mutex>

#include "Cache.h"

struct Backend
{
    std::string ip;
    int port;
    bool healthy;
};

class Proxy
{
private:

    Cache cache;

    std::vector<Backend> backends;

    size_t currentBackend;

    std::mutex backendMutex;

    std::string extractKey(const std::string& request);

    bool shouldCache(
        const std::string& request,
        const std::string& response
    );

    Backend getNextBackend();

public:

    Proxy();

    void handleClient(int clientSocket);
};