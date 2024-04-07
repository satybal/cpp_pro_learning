#include <iostream>

using namespace std;

// MATRIX N-dimentions
template <typename T, int DMS, T defval>
class Matrix
{
public:
    using Layer = Matrix<T, DMS - 1, defval>;

    T key;
    Matrix* next;

    ~Matrix()
    {
        auto iter = head;
        while (head != tail)
        {
            head = iter->next;
            delete iter;
            iter = head;
        }

        delete tail;
    }

    Layer* find(const T& key) const
    {
        auto iter = head;
        while (iter->key != key && iter != tail)
            iter = iter->next;

        return iter;
    }

    // Layer& operator[](const T& key)
    Layer& push(const T& key)
    {
        auto iter = find(key);

        if (iter != tail)
            return *iter;
        else
        {
            auto newLayer = tail;

            Layer* newEnd = new Layer;
            tail = newEnd;

            newLayer->key = key;
            newLayer->next = newEnd;

            return *newLayer;
        }
    }

    const Layer& operator[](const T& key) const
    {
        auto iter = find(key);
        return *iter;
    }


    int size() const
    {
        int sz = 0;
        auto iter = head;
        while (iter != tail)
        {
            sz += iter->size();
            iter = iter->next;
        }

        return sz;
    }
private:
    Layer* tail = new Layer;
    Layer* head = tail;
};

// MATRIX 0-dimention
template <typename T, T defval>
class Matrix<T, 0, defval>
{
public:
    Matrix():
        data(defval) {}

    T key;
    Matrix* next;

    Matrix& operator=(const T& value)
    {
        this->data = value;
        return *this;
    }

    int size() const
    {
        return 1;
    }
    
    friend std::ostream& operator<<
        (std::ostream &out, const Matrix& m)
    {
        out << m.data;
        return out;
    }
private:
    T data;
};