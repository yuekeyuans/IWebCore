#pragma once

#include <atomic>
#include <new>
#include <cstddef>

template <typename T>
class IObjectMemoryPoolUnit {
public:
    IObjectMemoryPoolUnit() = default;
    ~IObjectMemoryPoolUnit();

    template <typename... Args>
    T* allocate(Args&&... args);

    void deallocate(T* ptr);
    void releaseAll();

private:
    std::atomic<T*> m_stack{nullptr};
};

template<typename T>
IObjectMemoryPoolUnit<T>::~IObjectMemoryPoolUnit() {
    releaseAll();
}

template<typename T>
template <typename... Args>
T* IObjectMemoryPoolUnit<T>::allocate(Args&&... args) {
    T* old_head = m_stack.load(std::memory_order_acquire);

    while (old_head) {
        if (m_stack.compare_exchange_weak(old_head, *reinterpret_cast<T**>(old_head), std::memory_order_acquire, std::memory_order_relaxed)) {
            new (old_head) T(std::forward<Args>(args)...);
            return old_head;
        }
    }

    void* mem = ::operator new(sizeof(T));
    return new (mem) T(std::forward<Args>(args)...);
}

template<typename T>
void IObjectMemoryPoolUnit<T>::deallocate(T* ptr) {
    if(ptr == nullptr) return;

    ptr->~T();
    T* old_head = m_stack.load(std::memory_order_acquire);
    do {
        *reinterpret_cast<T**>(ptr) = old_head;
    } while (!m_stack.compare_exchange_weak(old_head, ptr, std::memory_order_release, std::memory_order_relaxed));
}

template<typename T>
void IObjectMemoryPoolUnit<T>::releaseAll() {
    T* node = m_stack.exchange(nullptr, std::memory_order_acquire);
    while (node) {
        T* next = *reinterpret_cast<T**>(node);
        node->~T();
        ::operator delete(node);
        node = next;
    }
}
