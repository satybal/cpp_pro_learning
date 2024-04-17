#pragma once

#include <vector>
#include "command.hpp"

class Handler
{
public:
    Handler(const char* range)
    {
        block = std::shared_ptr<Block>(new Block);
        block->set_range(std::stoi(std::string(range)));
        block->set_filename();
    }

    void send(std::string& input)
    {
        if (input[0] == '{')
        {
            open_block command(block, input);
            command.handle();
        }
        else if (input[0] == '}')
        {
            close_block command(block, input);
            command.handle();
        }
        else if (input.empty()) //EOF
        {
            eof command(block, input);
            command.handle();
        }
        else
        {
            any command(block, input);
            command.handle();
        }
    }
private:
    std::shared_ptr<Block> block;
};