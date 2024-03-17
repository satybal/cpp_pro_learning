#pragma once

#include <vector>
#include "allocator.hpp"

template <class T, size_t Capacity = 0, class Allocator = std::allocator<T>>
class Container
{
public:
    Container() noexcept: 
        size { 0 },
        capacity { Capacity }
        {
            data = alloc.allocate(capacity);
        }
    
    ~Container() noexcept 
    {
        alloc.deallocate(data, size);
    }

    void push_back(const T& value) 
    {
        // not necessary, since the functionality is not implemented
        
        // if (size == capacity)
        // {
        //     capacity = capacity * 2 + 1;
        //     T* newData = alloc.allocate(capacity);
        //     std::swap(newData, data);
        //     alloc.deallocate(newData, size);
        // }

        data[size] = value;
        ++size;

    }

    T operator[](const size_t& pos) 
    {
        return data[pos];
    }
            
private:
    T* data;
    size_t size;
    size_t capacity;

    Allocator alloc;
};
