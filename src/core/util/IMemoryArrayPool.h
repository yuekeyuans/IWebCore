#include <atomic>
#include <cstddef>
#include <new>

template <typename T>
class IMemoryArrayPool
{
private:
    struct Node {
        void* ptr;
        std::size_t size;
        Node* next;
    };

public:
    IMemoryArrayPool() = default;
    ~IMemoryArrayPool();
    T* allocateArray(std::size_t count);
    void deallocateArray(T* ptr, std::size_t count);
    void releaseAll();
    void freeNode(Node* node);

private:
    std::atomic<Node*> head{nullptr};
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
        if (node->size >= size) {
            if (head.compare_exchange_weak(node, node->next, std::memory_order_acquire)) {
                T* ptr = static_cast<T*>(node->ptr);
                delete node;
                return ptr;
            }
        } else {
            node = node->next;
        }
    }
    return static_cast<T*>(::operator new(size));
}

template <typename T>
void IMemoryArrayPool<T>::deallocateArray(T* ptr, std::size_t count)
{
    Node* newNode = new Node{ptr, sizeof(T) * count, nullptr};

    Node* oldHead = head.load(std::memory_order_acquire);
    do {
        newNode->next = oldHead;
    } while (!head.compare_exchange_weak(oldHead, newNode, std::memory_order_release));
}

template <typename T>
void IMemoryArrayPool<T>::releaseAll()
{
    Node* node = head.exchange(nullptr, std::memory_order_acquire);
    freeNode(node);
}

template <typename T>
void IMemoryArrayPool<T>::freeNode(Node* node) {
    while (node) {
        ::operator delete(node->ptr);
        Node* temp = node;
        node = node->next;
        delete temp;
    }
}
