#include<bits/stdc++.h>
class ThreadPool
{
public:

    ThreadPool(int numThreads);

    void enqueue(int clientSocket);

    ~ThreadPool();

private:
 std::vector<std::thread> workers;

std::queue<int> tasks;

std::mutex queueMutex;

std::condition_variable condition;

bool stop = false;
};