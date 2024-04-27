#pragma once

#include <cstddef>

class Allocator { //interface of basic alloc
protected:
    std::size_t m_totalSize;
    std::size_t m_used;   
    std::size_t m_peak;
public:
    
    explicit Allocator(const std::size_t totalSize) : m_totalSize { totalSize }, m_used { 0 }, m_peak { 0 } { }

    virtual ~Allocator() { m_totalSize = 0; }

    virtual void* Allocate(std::size_t size, std::size_t alignment = 0) = 0;

    virtual void Free(void* ptr) = 0;

    virtual void Init() = 0;

    friend class Benchmark;
};


