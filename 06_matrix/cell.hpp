#pragma once

#include <iostream>
#include "observer.hpp"

template <typename T, T defval>
struct Cell : public Observable
{
    T key, data = defval;

    void operator=(const T& value)
    {
        data = value;
        notifyObservers();
    }

    friend ostream& operator<<(ostream& os, Cell& c)
    {
        cout << c.data;
        return os;
    }

    bool operator==(const T& other) const
    {
        return data == other;
    }
};
