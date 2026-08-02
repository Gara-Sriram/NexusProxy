#pragma once
#include <Cache.h>
class Proxy
{
    private:
    Cache cache;
    std::string extractKey(const std::string& request);
public:
    void handleClient(int clientSocket);
    Proxy();
};