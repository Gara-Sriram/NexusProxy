#include "Cache.h"

Cache::Cache(int capacity)
{
    this->capacity = capacity;
}

bool Cache::get(const std::string& key,std::string& value){

    std::lock_guard<std::mutex> lock(cacheMutex);

    auto it = cacheMap.find(key);

    if(it == cacheMap.end())
    {
        return false;
    }

    cacheList.splice(
        cacheList.begin(),
        cacheList,
        it->second
    );

    value = it->second->value;

    return true;
}

void Cache::put(const std::string& key,const std::string& value){

    std::lock_guard<std::mutex> lock(cacheMutex);
    auto it = cacheMap.find(key);

    if(it != cacheMap.end())
    {
        it->second->value = value;

        cacheList.splice(
            cacheList.begin(),
            cacheList,
            it->second
        );

        return;
    }

    cacheList.push_front(
        {key,value}
    );

    cacheMap[key] =
        cacheList.begin();

    if(cacheList.size() > capacity)
    {
        cacheMap.erase(
            cacheList.back().key
        );

        cacheList.pop_back();
    }
}