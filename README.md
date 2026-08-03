# NexusProxy

A high-performance **multithreaded reverse proxy and load balancer** built in **Modern C++** using **POSIX sockets**, **thread pools**, **LRU caching**, and **Round Robin load balancing**. NexusProxy efficiently distributes incoming HTTP requests across multiple backend servers while providing intelligent caching, backend failover, configurable deployment, and thread-safe logging.

---

## Features

- 🚀 Multithreaded reverse proxy built using raw POSIX socket programming
- ⚡ Fixed-size thread pool for concurrent request processing
- 🔄 Round Robin load balancing across multiple backend servers
- 💾 Thread-safe LRU cache for HTTP GET responses
- ❤️ Passive backend health checks with automatic failover
- ⚙️ JSON-based configuration (ports, cache size, backend servers, thread count)
- 📝 Thread-safe logger with timestamps and thread IDs
- 🛑 Graceful shutdown using Linux signals
- 🏗 Modular object-oriented architecture

---

## Architecture

```
                    Client
                       │
                       ▼
             +-------------------+
             |    NexusProxy     |
             +-------------------+
                       │
        ┌──────────────┼──────────────┐
        ▼              ▼              ▼
   LRU Cache      Thread Pool     Logger
        │
        ▼
Round Robin Load Balancer
        │
 ┌──────┼────────┬────────┐
 ▼      ▼        ▼
9000   9001     9002
Backend Backend Backend
```

---

## How It Works

1. Client sends an HTTP request to NexusProxy.
2. Proxy extracts the requested resource.
3. Cache is checked for a previously stored response.
4. If cached, the response is immediately returned.
5. Otherwise, the Round Robin load balancer selects a healthy backend server.
6. Request is forwarded to the backend.
7. Backend response is streamed back to the client.
8. Cacheable responses (HTTP GET + 200 OK) are stored in the LRU cache.
9. Future requests for the same resource are served directly from cache.

---

## Implemented Features

### Reverse Proxy

- HTTP request forwarding
- Streaming response forwarding
- Persistent TCP socket communication
- Raw POSIX socket programming

---

### Thread Pool

- Fixed-size worker thread pool
- Producer-Consumer task queue
- Condition variable synchronization
- Efficient concurrent request handling

---

### Load Balancer

- Round Robin scheduling
- Thread-safe backend selection
- Automatic request distribution
- Passive backend failover

---

### LRU Cache

- Thread-safe implementation
- O(1) lookup
- O(1) insertion
- O(1) eviction
- HTTP GET response caching

---

### Backend Health Monitoring

When a backend connection fails:

- Backend is marked unhealthy
- Subsequent requests skip unhealthy servers
- Remaining healthy servers continue serving requests

---

### Configuration

Runtime configuration using `config.json`

Supports:

- Proxy Port
- Thread Pool Size
- Cache Size
- Backend Server List

---

### Logging

Each log entry contains:

- Timestamp
- Log Level
- Thread ID
- Message

Example:

```
[2026-08-03 18:35:16] [INFO] [Thread 140321456034560] CACHE HIT : /index.html

[2026-08-03 18:35:17] [ERROR] [Thread 140321447641856] Backend 9001 marked unhealthy
```

---

## Project Structure

```
NexusProxy/

├── include/
│   ├── Cache.h
│   ├── Config.h
│   ├── Logger.h
│   ├── Proxy.h
│   ├── Server.h
│   └── ThreadPool.h
│
├── src/
│   ├── Cache.cpp
│   ├── Config.cpp
│   ├── Logger.cpp
│   ├── Proxy.cpp
│   ├── Server.cpp
│   ├── ThreadPool.cpp
│   └── main.cpp
│
├── config.json
├── CMakeLists.txt
└── README.md
```

---

## Configuration

Example `config.json`

```json
{
    "proxy_port":8080,
    "thread_pool_size":4,
    "cache_size":100,
    "backends":[
        {
            "ip":"127.0.0.1",
            "port":9000
        },
        {
            "ip":"127.0.0.1",
            "port":9001
        },
        {
            "ip":"127.0.0.1",
            "port":9002
        }
    ]
}
```

---

## Build

### Install Dependencies

Ubuntu

```bash
sudo apt update

sudo apt install build-essential cmake

sudo apt install nlohmann-json3-dev
```

---

### Clone Repository

```bash
git clone https://github.com/Gara-Sriram/NexusProxy.git

cd NexusProxy
```

---

### Build

```bash
mkdir build

cd build

cmake ..

make
```

---

### Run

```bash
./NexusProxy
```

---

## Request Flow

```
                Client
                   │
                   ▼
             Receive Request
                   │
                   ▼
             Extract URL
                   │
                   ▼
             Check Cache
          ┌────────┴────────┐
          │                 │
      Cache Hit         Cache Miss
          │                 │
          ▼                 ▼
 Return Cached      Round Robin Scheduler
    Response               │
                            ▼
                    Select Healthy Backend
                            │
                            ▼
                      Connect Backend
                            │
                            ▼
                    Forward HTTP Request
                            │
                            ▼
                  Receive Backend Response
                            │
                            ▼
                 Cache (GET + 200 OK Only)
                            │
                            ▼
                    Return Client Response
```

---

## Technologies Used

- Modern C++17
- POSIX Sockets
- Linux System Calls
- Multithreading
- Mutexes
- Condition Variables
- LRU Cache
- CMake
- nlohmann/json
- JSON Configuration
- Object-Oriented Design

---

## Future Improvements

- Active backend health checks
- HTTPS support using OpenSSL
- Weighted Round Robin
- Least Connections load balancing
- Gzip compression
- Rate limiting
- Prometheus metrics
- Docker deployment
- HTTP/2 support
- Admin dashboard

---

## Learning Outcomes

This project demonstrates practical implementation of:

- TCP Socket Programming
- HTTP Request Processing
- Concurrent Programming
- Thread Pool Design Pattern
- Producer-Consumer Synchronization
- Thread-safe Data Structures
- Load Balancing Algorithms
- LRU Cache Design
- Fault Tolerance
- System Design Principles
- Modern C++ Programming
- Linux Network Programming

---

## License

This project is developed for learning modern backend systems, concurrent programming, networking, and systems programming concepts.