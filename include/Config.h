#pragma once

#include <string>
#include <vector>

struct BackendConfig
{
    std::string ip;
    int port;
};

class Config
{
public:

    int proxyPort;

    int threadPoolSize;

    int cacheSize;

    std::vector<BackendConfig> backends;

    bool load(const std::string& filename);
};