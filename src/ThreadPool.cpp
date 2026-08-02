#include "ThreadPool.h"

ThreadPool::ThreadPool(int numThreads)
{
    stop = false;

    for (int i = 0; i < numThreads; i++)
    {
        workers.emplace_back([this]()
        {
            while (true)
            {
                std::unique_lock<std::mutex> lock(queueMutex);

                condition.wait(lock, [this]()
                {
                    return stop || !tasks.empty();
                });

                if (stop && tasks.empty())
                {
                    return;
                }

                int clientSocket = tasks.front();
                tasks.pop();

                lock.unlock();

                proxy.handleClient(clientSocket);
            }
        });
    }
}

void ThreadPool::enqueue(int clientSocket)
{
        {
        std::unique_lock<std::mutex> lock(queueMutex);

        tasks.push(clientSocket);
    } // lock is destroyed here, mutex is unlocked

    condition.notify_one();
}

ThreadPool::~ThreadPool()
{
   {
    std::unique_lock<std::mutex> lock(queueMutex);

    stop = true;
   }
    condition.notify_all();

   for(auto &worker : workers){
        if (worker.joinable()){
        worker.join();
    }
   }
   
}