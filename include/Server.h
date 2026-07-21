#pragma once

class Server
{
private:

    int port;

    int serverSocket;

public:

    Server(int port);

    bool start();

    void run();
};