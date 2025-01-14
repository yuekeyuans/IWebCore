#include <atomic>
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
    struct Node {
        void* ptr;        // 指向内存的指针
        std::size_t size; // 缓存的数组大小（字节数）
        Node* next;       // 指向下一个节点
    };

    std::atomic<Node*> head{nullptr}; // 无锁栈的头指针

    void freeNode(Node* node); // 递归释放节点
};

template <typename T>
IMemoryArrayPool<T>::~IMemoryArrayPool() {
    releaseAll();
}

template <typename T>
T* IMemoryArrayPool<T>::allocateArray(std::size_t count) {
    std::size_t size = sizeof(T) * count;
    Node* node = head.load(std::memory_order_acquire);

    while (node) {
        // 遍历无锁栈，尝试取出符合大小的内存块
        if (node->size >= size) {
            if (head.compare_exchange_weak(node, node->next, std::memory_order_acquire)) {
                T* ptr = static_cast<T*>(node->ptr);
                delete node; // 释放栈节点（但不释放内存）
                return ptr;
            }
        } else {
            node = node->next;
        }
    }

    // 如果没有找到合适的内存块，则分配新内存
    return static_cast<T*>(::operator new(size));
}

template <typename T>
void IMemoryArrayPool<T>::deallocateArray(T* ptr, std::size_t count) {
    if (!ptr) return;

    // 创建一个新的栈节点
    Node* newNode = new Node{ptr, sizeof(T) * count, nullptr};

    // 将节点无锁地推入栈
    Node* oldHead = head.load(std::memory_order_acquire);
    do {
        newNode->next = oldHead;
    } while (!head.compare_exchange_weak(oldHead, newNode, std::memory_order_release));
}

template <typename T>
void IMemoryArrayPool<T>::releaseAll() {
    Node* node = head.exchange(nullptr, std::memory_order_acquire); // 原子清空栈
    freeNode(node); // 释放所有栈节点及其内存
}

template <typename T>
void IMemoryArrayPool<T>::freeNode(Node* node) {
    while (node) {
        ::operator delete(node->ptr); // 释放内存块
        Node* temp = node;
        node = node->next;
        delete temp; // 释放栈节点
    }
}
