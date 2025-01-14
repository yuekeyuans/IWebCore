#pragma once

#include <vector>
#include <mutex>
#include <cstddef>
#include <new>

template <typename T>
class IMemoryArrayPool {
public:
    IMemoryArrayPool() = default;
    ~IMemoryArrayPool();

    // 分配固定大小的数组
    T* allocateArray(std::size_t count);

    // 回收固定大小的数组
    void deallocateArray(T* ptr, std::size_t count);

    // 释放缓存中所有未使用的数组
    void releaseAll();

private:
    struct CacheEntry {
        void* ptr;        // 指向内存的指针
        std::size_t size; // 缓存的数组大小（字节数）
    };

    std::vector<CacheEntry> arrayCache; // 缓存池
    std::mutex mutex_;                  // 互斥锁保护
};

template <typename T>
IMemoryArrayPool<T>::~IMemoryArrayPool() {
    releaseAll();
}

template <typename T>
T* IMemoryArrayPool<T>::allocateArray(std::size_t count) {

        return static_cast<T*>(::operator new(count));
//    std::lock_guard<std::mutex> lock(mutex_);
//    std::size_t size = sizeof(T) * count;

//    // 查找适合的缓存
//    for (auto it = arrayCache.begin(); it != arrayCache.end(); ++it) {
//        if (it->size >= size) {
//            void* ptr = it->ptr;
//            arrayCache.erase(it); // 从缓存中移除已使用的内存
//            return static_cast<T*>(ptr);
//        }
//    }

    // 如果没有合适的缓存，则分配新内存
//    return static_cast<T*>(::operator new(size));
}

template <typename T>
void IMemoryArrayPool<T>::deallocateArray(T* ptr, std::size_t count) {
    delete [] ptr;
//    if (ptr) {
//        std::lock_guard<std::mutex> lock(mutex_);
//        arrayCache.push_back({ptr, sizeof(T) * count}); // 回收到缓存池
//    }
}

template <typename T>
void IMemoryArrayPool<T>::releaseAll() {
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto& entry : arrayCache) {
        ::operator delete(entry.ptr); // 释放缓存的内存
    }
    arrayCache.clear(); // 清空缓存池
}
