#pragma once

#include "row.hpp"

template <typename T, T defval>
struct Matrix : public Observer
{
    using TRow = Row<T, defval>;
    using URow = unique_ptr<TRow>;

    list<URow> rows;
    URow empty_row = URow(new TRow);

    TRow& operator[](const int& key)
    {
        auto it = find_if(rows.begin(),
                          rows.end(),
                          [&] (auto& c) { return key == c->key; });

        if (it != rows.end())
            return **it;
        else
        {
            empty_row->key = key;
            empty_row->addObserver(this);

            return *empty_row;
        }
    }

    virtual void update() override
    {
        rows.remove_if([](auto& r){ return r->size() == 0; });
        rows.push_back(std::move(empty_row));
        empty_row = URow(new TRow);
    }

    int size()
    {   
        int _size = 0;
        for (auto &row: rows)
            _size += row->size();

        return _size;
    }

    void print()
    {
        for(auto& r: rows)
            for (auto& c: r->cells)
                cout << "matrix ["
                     << r->key << "][" 
                     << c->key << "]: "
                     << c->data << endl;
    }
};
