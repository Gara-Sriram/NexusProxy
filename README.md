# NexusProxy

A multithreaded reverse proxy and load balancer built from scratch in C++ using POSIX sockets.

## Current Features

- Reverse proxy implementation
- HTTP request forwarding
- TCP socket programming
- Browser → Proxy → Backend communication
- Object-oriented architecture

## Project Structure

```
NexusProxy
│
├── include
│   ├── Server.h
│   └── Proxy.h
│
├── src
│   ├── main.cpp
│   ├── Server.cpp
│   └── Proxy.cpp
│
├── backend
│   └── backend.cpp
│
└── CMakeLists.txt
```

## Upcoming Features

- Thread Pool
- Round Robin Load Balancing
- Config File
- Logging
- LRU Cache
- Graceful Shutdown

## Technologies

- C++17
- POSIX Sockets
- CMake
- Linux

## Build

```bash
mkdir build
cd build
cmake ..
make
```

## Status

🚧 Work in Progress