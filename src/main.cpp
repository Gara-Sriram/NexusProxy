#include "Server.h"
#include "Config.h"
#include <csignal>
Server* globalServer=nullptr;
volatile sig_atomic_t running = 1;
void signalHandler(int)
{
    if(globalServer)
    {
        globalServer->stop();
    }
}
int main()
{
    Config config;
    signal(
    SIGINT,
    signalHandler
);
    if(!config.load("config.json"))
    {
        return 1;
    }

   Server server(config);

globalServer=&server;

    if(!server.start())
    {
        return 1;
    }

    server.run();

    return 0;
}