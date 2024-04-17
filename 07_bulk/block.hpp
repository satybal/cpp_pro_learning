#pragma once

#include <vector>
#include <iostream>
#include <chrono>
#include <fstream>

class Block
{
public:
    void add_nesting()
    {
        ++nested;
    }

    void remove_nesting()
    {
        --nested;
    }

    size_t& get_nesting()
    {
        return nested;
    }

    int& get_range()
    {
        return range;
    }

    void set_range(const int& r)
    {
        range = r;
    }

    bool empty()
    {
        return lines.empty();
    }

    void push(std::string& command)
    {
        lines.push_back(command);
    }

    int size()
    {
        return lines.size();
    }

    void set_filename()
    {
        filename = create_file_name();
    }

    Block& print()
    {
        if (!empty())
        {
            to_stream(std::cout);

            std::ofstream file(filename);
            to_stream(file);
        }
        
        return *this;
    }

    void reset()
    {
        lines.clear();
        set_filename();
    }
    
private:
    int range;
    size_t nested = 0;
    std::vector<std::string> lines;
    std::string filename;

    void to_stream(std::ostream& stream)
    {
        stream << "bulk: ";

        for (auto it = lines.begin(); it != lines.end();)
        {
            stream << *it;
            ++it;

            if (it != lines.end())
                stream << ", ";
        }
            
        stream << std::endl;
    }

    std::string create_file_name()
    {
        const auto tm = std::chrono::system_clock::now();
        const auto tmt = std::chrono::system_clock::to_time_t(tm);
        const auto ltm = *std::gmtime(&tmt);
        const auto ms = std::chrono::time_point_cast<std::chrono::milliseconds>(tm)
            .time_since_epoch().count() % 1000;
        char time_buf[100];
        std::strftime(time_buf, 100, "%H%M%S", &ltm);

        auto fname = std::string("bulk") + std::string(time_buf) + std::to_string(ms) + std::string(".log");

        return fname;
    }
};
