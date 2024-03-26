#pragma once

#include <vector>
#include "allocator.hpp"

template <class T, class Allocator = std::allocator<T>>
class Container
{
public:
    Container() noexcept: 
        size { 0 },
        capacity { 0 }
        {
            data = alloc.allocate(capacity);
        }
    
    ~Container() noexcept 
        {
            alloc.deallocate(data, capacity);
        }

    void push_back(const T& value) 
    {        
        if (size == capacity)
        {
            capacity = capacity * 2 + 1;
            T* newData = alloc.allocate(capacity);
            
            for (size_t i = 0; i < size; ++i)
                newData[i] = data[i];

            std::swap(newData, data);
            alloc.deallocate(newData, size);
        }

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
