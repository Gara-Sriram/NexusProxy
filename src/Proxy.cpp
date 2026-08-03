#include "Proxy.h"

#include <sstream>
#include <iostream>
#include <cstring>
#include <Logger.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

Proxy::Proxy(const Config& config)
    : cache(config.cacheSize),
      currentBackend(0)
{
    for(const auto& backend : config.backends)
    {
        backends.push_back(
        {
            backend.ip,
            backend.port,
            true
        });
    }
}
void Proxy::markBackendUnhealthy(int port)
{
    std::lock_guard<std::mutex> lock(backendMutex);

    for(auto &backend : backends)
    {
        if(backend.port == port)
        {
            backend.healthy = false;

            Logger::error(
                "Backend "
                + std::to_string(port)
                + " marked unhealthy"
            );

            break;
        }
    }
}
int Proxy::connectToBackend(Backend &backend)
{
    for(size_t i = 0; i < backends.size(); i++)
    {
        backend = getNextBackend();
          if(backend.port == -1){
        break;
    }
        int backendSocket =
            socket(AF_INET, SOCK_STREAM, 0);

        if(backendSocket == -1)
        {
            continue;
        }

        sockaddr_in backendAddr{};

        backendAddr.sin_family = AF_INET;
        backendAddr.sin_port = htons(backend.port);

        inet_pton(
            AF_INET,
            backend.ip.c_str(),
            &backendAddr.sin_addr
        );
        Logger::info("Trying backend " +backend.ip +":" +std::to_string(backend.port));
        if(connect(backendSocket,(sockaddr*)&backendAddr,sizeof(backendAddr)) == -1){
  
            markBackendUnhealthy(backend.port);

            close(backendSocket);

            continue;
        }

        return backendSocket;
    }

    return -1;
}
Backend Proxy::getNextBackend()
{
    std::lock_guard<std::mutex> lock(backendMutex);

    for(size_t i=0;i<backends.size();i++)
    {
        Backend backend = backends[currentBackend];

        currentBackend =
            (currentBackend+1)
            %
            backends.size();

        if(backend.healthy)
        {
            return backend;
        }
    }

    return {"",-1,false};
}
std::string Proxy::extractKey(const std::string& request){
    std::stringstream ss(request);

    std::string method;
    std::string path;

    ss >> method;
    ss >> path;

    return path;
}
bool Proxy::shouldCache(const std::string& request,const std::string& response){
    std::stringstream ss(request);

    std::string method;

    ss >> method;

    if(method!="GET")
    {
        return false;
    }

    if(response.find("200 OK")==std::string::npos)
    {
        return false;
    }

    return true;
}
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


    std::string requestString(request, bytesReceived);
    std::string key = extractKey(requestString);
    
    // Step 2: Check Cache

    std::string cachedResponse;

    if (cache.get(key, cachedResponse))
    {
        Logger::info("CACHE HIT : " + key);

        send(
            clientSocket,
            cachedResponse.c_str(),
            cachedResponse.size(),
            0
        );

        close(clientSocket);
        return;
    }

   Logger::info("CACHE MISS : " + key);
    // Step 3: Create backend socket

  Backend backend;

int backendSocket =
    connectToBackend(backend);


if(backendSocket == -1)
{
    Logger::error("All backends are unavailable");

    close(clientSocket);

    return;
}

    // Step 4: Forward request

    send(
        backendSocket,
        request,
        bytesReceived,
        0
    );

    // Step 5: Receive backend response


char buffer[4096];

    std::string completeResponse;

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
        // Build complete response for cache
        completeResponse.append(
            buffer,
            bytesReceived
        );

    send(
        clientSocket,
        buffer,
        bytesReceived,
        0
    );
}

    // Step 8: adding to cache

    if(shouldCache(requestString,completeResponse)){
    cache.put(
        key,
        completeResponse
    );

   Logger::info("CACHE STORE : " + key);
}

    // Step 9: Cleanup

    close(backendSocket);
    close(clientSocket);
}