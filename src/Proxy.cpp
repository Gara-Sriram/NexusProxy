#include "Proxy.h"

#include <iostream>
#include <cstring>
#include <Logger.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

void Proxy::handleClient(int clientSocket)
{
    // Step 1: Receive request from browser

    char request[8192] = {0};

    int bytesReceived = recv(
        clientSocket,
        request,
        sizeof(request),
        0
    );

    if (bytesReceived <= 0)
    {
        
        Logger::error("Failed to receive client request");
        close(clientSocket);
        return;
    }
     Logger::info("========== HTTP Request ==========");

    std::cout << request << std::endl;

    // Step 2: Create backend socket

    int backendSocket = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

    if (backendSocket == -1)
    {
       
         Logger::error("Failed to create backend socket");
        close(clientSocket);
        return;
    }

    // Step 3: Backend address

    sockaddr_in backendAddr{};

    backendAddr.sin_family = AF_INET;
    backendAddr.sin_port = htons(9000);

    inet_pton(
        AF_INET,
        "127.0.0.1",
        &backendAddr.sin_addr
    );

    // Step 4: Connect to backend
  

    if (connect(
            backendSocket,
            (sockaddr*)&backendAddr,
            sizeof(backendAddr)
        ) == -1)
    {
       
        Logger::error("Failed to connect to backend");
        close(backendSocket);
        close(clientSocket);

        return;
    }

    // Step 5: Forward request

    send(
        backendSocket,
        request,
        bytesReceived,
        0
    );

    // Step 6: Receive backend response


char buffer[4096];

while(true)
{
    int bytesReceived =
        recv(
            backendSocket,
            buffer,
            sizeof(buffer),
            0
        );

    if(bytesReceived<=0)
        break;

    send(
        clientSocket,
        buffer,
        bytesReceived,
        0
    );
}

    // Step 7: Forward response


    

    // Step 8: Cleanup


    close(backendSocket);
    close(clientSocket);
}