#include "Server.h"

#include <iostream>
#include<Logger.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

Server::Server(int port)
    : port(port),
      serverSocket(-1),
      threadPool(4)
{
}

bool Server::start()
{
    // Step 1: Create socket
    serverSocket = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

    if (serverSocket == -1)
    {
        Logger::error("Failed to create server socket");
        return false;
    }

    // Step 2: Server address
    sockaddr_in serverAddr{};

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Step 3: Bind socket
    if (bind(
            serverSocket,
            (sockaddr*)&serverAddr,
            sizeof(serverAddr)
        ) == -1)
    {
       
         Logger::error("Failed to bind server socket");
        close(serverSocket);

        return false;
    }

    // Step 4: Listen
    if (listen(serverSocket, 10) == -1)
    {
        
        Logger::error("Failed to listen");
        close(serverSocket);

        return false;
    }

   Logger::info("Server listening");

    return true;
}

void Server::run()
{
    while (true)
    {
        int clientSocket =
            accept(
                serverSocket,
                nullptr,
                nullptr
            );

        if (clientSocket == -1)
        {
            
            Logger::error("Failed to accept client");
            continue;
        }

        
        Logger::info("Client Connected");
        threadPool.enqueue(clientSocket);
    }
}