#pragma once
#include <mutex>
#include <string>
#include <list>
#include <unordered_map>

struct CacheEntry
{
    std::string key;
    std::string value;
};

class Cache
{
private:

    int capacity;

    std::list<CacheEntry> cacheList;

    std::unordered_map<
        std::string,
        std::list<CacheEntry>::iterator
    > cacheMap;
    std::mutex cacheMutex;

public:

    Cache(int capacity);

    bool get(const std::string& key,std::string& value);

    void put(const std::string& key,const std::string& value);
};