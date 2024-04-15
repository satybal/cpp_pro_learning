#pragma once

#include <list>
#include <algorithm>
#include <memory>
#include "cell.hpp"

template <typename T, T defval>
struct Row : public Observer, Observable
{
    using TCell = Cell<T, defval>;
    using UCell = unique_ptr<TCell>;

    T key;
    list<UCell> cells;
    UCell empty_cell = UCell(new TCell);

    TCell& operator[](const int& key)
    {
        auto it = find_if(cells.begin(),
                          cells.end(),
                          [&] (auto& c) { return key == c->key; });

        if (it != cells.end())
            return **it;
        else
        {
            empty_cell->key = key;
            empty_cell->addObserver(this);

            return *empty_cell;
        }
    }

    virtual void update() override
    {
        cells.remove_if([](auto& c){ return c->data == defval; });

        if (empty_cell->data == defval)
            empty_cell.reset();
        else
        {
            cells.push_back(std::move(empty_cell));
            notifyObservers();
        }
            
        empty_cell = UCell(new TCell);
    }

    int size()
    {
        return cells.size();
    }
};
