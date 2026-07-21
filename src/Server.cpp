#include "Server.h"
#include <iostream>      // Required for std::cout
#include <sys/socket.h>  // Required for socket, bind, listen, setsockopt
#include <netinet/in.h>
#include <unistd.h>

Server::Server(int port)
{
    this->port = port;
    serverSocket = -1;
}
bool Server::start()
{
    serverSocket = socket(AF_INET,
                          SOCK_STREAM,
                          0);

    if(serverSocket==-1)
    {
        std::cout<<"Socket Error\n";
        return false;
    }
    sockaddr_in serverAddr{};

serverAddr.sin_family=AF_INET;

serverAddr.sin_port=htons(port);

serverAddr.sin_addr.s_addr=INADDR_ANY;
if(bind(serverSocket,
        (sockaddr*)&serverAddr,
        sizeof(serverAddr))==-1)
{
    std::cout<<"Bind Error\n";

    return false;
}
if(listen(serverSocket,10)==-1)
{
    std::cout<<"Listen Error\n";

    return false;
}
std::cout<<"Server Started\n";

return true;
}
void Server::run()
{
    while(true)
    {
        int clientSocket=
        accept(serverSocket,
               nullptr,
               nullptr);

        if(clientSocket==-1)
            continue;

        std::cout<<"Client Connected\n";

        close(clientSocket);
    }
}