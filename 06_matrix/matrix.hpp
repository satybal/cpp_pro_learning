#include <iostream>

using namespace std;

template <typename T, int DMS>
class Matrix
{
    // friend class iterator;
    using Layer = Matrix<T, DMS - 1>;

    Layer* _end = new Layer;
    Layer* _begin = _end;

public:
    
    T key;
    Matrix* next;

    // class iterator
    // {
    //     friend class IMatrix;

    //     Layer* ptr;

    //     iterator(Layer* ptr): ptr(ptr) {}

    // public:

    //     iterator(const iterator& it): ptr(it.ptr) {}

    //     bool operator!=(const iterator& other)
    //     {
    //         return this->ptr != other.ptr;
    //     }

    //     bool operator==(const iterator& other)
    //     {
    //         return this->ptr == other.ptr;
    //     }

    //     iterator operator++()
    //     {
    //         ptr = ptr->next;
    //         return *this;
    //     }

    //     Layer& operator*()
    //     {
    //         return *ptr;
    //     }

    //     Layer* pointer()
    //     {
    //         return ptr;
    //     }

    // };

    // iterator begin()
    // {
    //     return _begin;
    // }

    // iterator end()
    // {
    //     return _end;
    // }

    ~Matrix()
    {
        auto iter = _begin;
        while (_begin != _end)
        {
            _begin = iter->next;
            delete iter;
            iter = _begin;
        }

        delete _end;
    }

    Layer* find(const T& key)
    {
        auto iter = _begin;
        while (iter->key != key && iter != _end)
            iter = iter->next;

        return iter;
    }

    Layer& operator[](const T& key)
    {
        auto iter = find(key);

        if (iter != _end)
            return *iter;
        else
        {
            auto newLayer = _end;

            Layer* newEnd = new Layer;
            _end = newEnd;

            newLayer->key = key;
            newLayer->next = newEnd;

            return *newLayer;
        }
    }

    // TODO const operator[]

    int size()
    {
        int sz = 0;
        auto iter = _begin;
        while (iter != _end)
        {
            sz += iter->size();
            iter = iter->next;
        }

        return sz;
    }
};

template <typename T>
class Matrix<T, 0>
{
    T data;

public:

    T key;
    Matrix* next;

    T& operator=(const T& value)
    {
        return data = value;
    }

    int size()
    {
        return 1;
    }
    
    friend std::ostream& operator<<
        (std::ostream &out, const Matrix& m)
    {
        out << m.data;
        return out;
    }
};
