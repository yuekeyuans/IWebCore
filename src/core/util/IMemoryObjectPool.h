#pragma once

#include <atomic>
#include <cstddef>
#include <new>

template <typename T>
class IMemoryObjectPool
{
public:
    IMemoryObjectPool() = default;
    ~IMemoryObjectPool();

public:
    template <typename... Args>
    T* allocate(Args&&... args);
    void deallocate(T* ptr);
    void releaseAll();

private:
    struct Node {
        T* object;       // 实际存储的对象
        Node* next;      // 指向下一个节点
    };

    std::atomic<Node*> m_stack{nullptr}; // 栈的顶端（无锁栈）
};

template<typename T>
IMemoryObjectPool<T>::~IMemoryObjectPool() {
    releaseAll();
}

template<typename T>
template <typename... Args>
T* IMemoryObjectPool<T>::allocate(Args&&... args)
{
    Node* old_head = m_stack.load(std::memory_order_acquire);
    while (old_head) {
        // 尝试弹出栈顶节点
        if (m_stack.compare_exchange_weak(old_head, old_head->next, std::memory_order_acquire, std::memory_order_relaxed)) {
            T* obj = old_head->object;
            delete old_head;  // 释放节点本身
            new (obj) T(std::forward<Args>(args)...);  // 使用 placement new 构造对象
            return obj;
        }
    }

    // 如果栈为空，分配新内存
    void* mem = ::operator new(sizeof(T));
    return new (mem) T(std::forward<Args>(args)...);  // 使用 placement new
}

template<typename T>
void IMemoryObjectPool<T>::deallocate(T* ptr)
{
    ptr->~T();  // 显式调用析构函数

    // 创建新节点存储对象
    Node* new_node = new Node{ptr, nullptr};
    Node* old_head = m_stack.load(std::memory_order_acquire);

    do {
        new_node->next = old_head;  // 新节点指向当前栈顶
    } while (!m_stack.compare_exchange_weak(old_head, new_node, std::memory_order_release, std::memory_order_relaxed));

}

template<typename T>
void IMemoryObjectPool<T>::releaseAll()
{
    Node* node = m_stack.exchange(nullptr, std::memory_order_acquire); // 清空栈

    while (node) {
        Node* next = node->next;
        node->object->~T();           // 调用对象的析构函数
        ::operator delete(node->object); // 释放对象的内存
        delete node;                  // 释放节点本身
        node = next;
    }
}
