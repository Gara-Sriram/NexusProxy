#include "Config.h"

#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool Config::load(const std::string& filename)
{
    std::ifstream input(filename);

    if(!input)
    {
        std::cerr
            << "Failed to open "
            << filename
            << std::endl;

        return false;
    }

    json data;

    input >> data;

    proxyPort =
        data["proxy_port"];

    threadPoolSize =
        data["thread_pool_size"];

    cacheSize =
        data["cache_size"];

    for(auto &backend : data["backends"])
    {
        BackendConfig b;

        b.ip =
            backend["ip"];

        b.port =
            backend["port"];

        backends.push_back(b);
    }

    return true;
}