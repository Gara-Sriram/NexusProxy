#pragma once

#include "ThreadPool.h"
#include "Config.h"

class Server
{
private:

    int serverSocket;

    int port;
    bool running;
    ThreadPool threadPool;

public:

    Server(const Config& config);

    bool start();

    void run();
    void stop();
};