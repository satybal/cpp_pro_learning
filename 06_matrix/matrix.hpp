#include <unordered_map>
#include <iostream>
#include <memory>

using namespace std;

template <typename T, int DMS, T defval>
class Matrix
{
public:
    using UpLayer   = Matrix<T, DMS + 1, defval>; 
    using DownLayer = Matrix<T, DMS - 1, defval>;

    DownLayer& operator[](const T& key)
    {
        m_key = key;
        if (m_line.contains(key))
            return *(m_line[key]);
        else
        {
            new_layer->set_up_layer(this);
            return *new_layer;
        }
    }

    template <int D = DMS>
    typename enable_if< (D == 1), void >::type
    update()
    {
        m_line[m_key] = move(new_layer);

        if (m_line.size() == 1)
            up->update();

        new_layer = unique_ptr<DownLayer>(new DownLayer);
    }

    template <int D = DMS>
    typename enable_if< (D > 1), void >::type
    update() 
    {
        m_line[m_key] = move(new_layer);
        new_layer = unique_ptr<DownLayer>(new DownLayer);
    }

    template <int D = DMS>
    typename enable_if<(D > 1), int>::type
    size()
    {
        int _size = 0;

        for (auto& [key, value]: m_line)
            _size += value->size();

        return _size;
    }

    template <int D = DMS>
    typename enable_if< (D == 1), int>::type
    size()
    {
        return m_line.size();
    }

    void set_up_layer(UpLayer* u)
    {
        up = u;
    }

    template <int D = DMS>
    typename enable_if<(D == 1), void>::type
    erase()
    {
        m_line.erase(m_key);
        if (m_line.empty())
            up->erase();
    }

    template <int D = DMS>
    typename enable_if<(D > 1), void>::type
    erase()
    {
        m_line.erase(m_key);
    }

private:
    T m_key;
    UpLayer* up;
    unordered_map<T, unique_ptr<DownLayer>> m_line;
    unique_ptr<DownLayer> new_layer = unique_ptr<DownLayer>(new DownLayer);
};

// #########################################
template <typename T, T defval>
class Matrix<T, 0, defval>
{
public:
    using UpLayer = Matrix<T, 1, defval>;

    void operator=(const T& value)
    {
        if (value == defval)
            up->erase();
        else if (data == defval)
        {
            data = value;
            up->update();
        }
        else
            data = value;
    }

    friend ostream& operator<<(ostream& os, Matrix& m)
    {
        os << m.data;
        return os;
    }

    void set_up_layer(UpLayer* u)
    {
        up = u;
    }

    bool operator==(const T& value)
    {
        return data == value;
    }

private:
    T data = defval;
    UpLayer* up;
};