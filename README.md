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
## ✅ Completed

- Reverse proxy using POSIX sockets
- HTTP request forwarding
- Multithreaded request handling using a fixed-size thread pool
- Producer–Consumer task queue with mutex and condition variables
- Thread-safe LRU cache implementation
- Modular project architecture (Server, Proxy, ThreadPool, Cache, Logger)

## 🚧 In Progress

- Cache integration with proxy
- Round-robin load balancing
- External configuration support
- Enhanced logging
- Performance benchmarking