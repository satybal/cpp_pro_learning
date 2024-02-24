#include <memory>
#include <new>

template <class T>
struct MyAllocator : public std::allocator_traits <T>
{
    using value_type = T;

    std::shared_ptr<void> Pool;
    size_t PoolSize;
    size_t RestMem;

    MyAllocator(const size_t& p_size) noexcept : PoolSize(p_size) 
    {
        Pool = ::operator new(PoolSize * sizeof(T));
    }

    T* allocate(size_t n)
    {
        if ((RestMem -= n) < 0) {
            throw std::bad_alloc{};
        }
        
        return static_cast<T*>(n * sizeof(T));
    }

    void deallocate(T* p, size_t n) 
    {

    }

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;
};

struct deleter
{
    void operator()(void* ptr)
    {
        ::operator delete(ptr);
    }
};
