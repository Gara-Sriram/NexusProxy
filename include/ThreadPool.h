#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "Proxy.h"

class ThreadPool
{
private:
    std::vector<std::thread> workers;
    std::queue<int> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;

    bool stop;

    Proxy proxy;

public:
   ThreadPool(
    int numThreads,
    const Config& config
);

    void enqueue(int clientSocket);

    ~ThreadPool();
};