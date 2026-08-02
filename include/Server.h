#pragma once

#include "ThreadPool.h"

class Server
{
private:
    int serverSocket;
    int port;

    ThreadPool threadPool;

public:
    Server(int port);

    bool start();

    void run();
};