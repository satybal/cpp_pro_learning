#pragma once

#include <memory>

struct deleter
{
    void operator()(void* ptr)
    {
        ::operator delete(ptr);
    }
};

template <class T, size_t Size>
struct Allocator {
    using value_type = T;

    Allocator() noexcept:
        pool_size { Size },
        mem_busy { 0 },
        mem_pool { ::operator new(sizeof(T) * pool_size), deleter() }
        {}

    template <class U, size_t USize = Size> Allocator (const Allocator<U, USize>& other) noexcept:
        mem_pool{other.mem_pool} 
        {}
  
    template <class U, size_t USize = Size>
    struct rebind
    {
        typedef Allocator<U, USize> other;
    };

    T* allocate (std::size_t n) 
    {
        mem_busy += n;
        return pointer + mem_busy - n;
    }

    void deallocate (T*, std::size_t) 
    {
        mem_busy = 0;
    }

private:
    size_t pool_size;
    size_t mem_busy;
    std::shared_ptr<void> mem_pool;
    T* pointer = static_cast<T*>(mem_pool.get());
};

template <class T, class U, size_t Size>
constexpr bool operator==(const Allocator<T, Size>& lhs, const Allocator<U, Size>& rhs) noexcept 
{
    return lhs.mem_pool == rhs.mem_pool;
}

template <class T, class U, size_t Size>
constexpr bool operator!=(const Allocator<T, Size>& lhs, const Allocator<U, Size>& rhs) noexcept 
{
    return lhs.mem_pool != rhs.mem_pool;
}
