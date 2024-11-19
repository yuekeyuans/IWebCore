#pragma once


class IStackObjectUnit
{
public:
    IStackObjectUnit() = default;

private:    // only run  in stack
    void* operator new[] (std::size_t size) = delete;
    void* operator new[] (std::size_t size, const std::nothrow_t& nothrow_value) = delete;
    void* operator new[] (std::size_t size, void* ptr) = delete;
    void* operator new(std::size_t) = delete;
    void* operator new(std::size_t, void*) = delete;
    void* operator new (std::size_t size, const std::nothrow_t& nothrow_value) throw() = delete;

    void operator delete[] (void* ptr) throw() = delete;
    void operator delete[] (void* ptr, const std::nothrow_t& nothrow_constant) throw() = delete;
    void operator delete[] (void* ptr, void* voidptr2) throw() = delete;
    void operator delete( void * ) = delete;
    void operator delete( void *, size_t ) = delete;
};

