#pragma once

#include <memory>
#include "block.hpp"

struct ICommand
{
    ICommand(std::shared_ptr<Block>& block, std::string& line):
        block(block),
        line(line)
        {}

    virtual void handle() = 0;
    
    std::shared_ptr<Block> block;
    std::string line;
};

struct any : public ICommand // any command
{
    using ICommand::ICommand;
    virtual void handle() override
    {
        block->push(line);
        if (block->size() == block->get_range() && block->get_nesting() == 0)
            block->print().reset();
    }
};

struct open_block : public ICommand // {
{
    using ICommand::ICommand;
    virtual void handle() override
    {
        if (block->get_nesting() == 0) 
            block->print().reset();
            
        block->add_nesting();
    }
};

struct close_block : public ICommand // }
{
    using ICommand::ICommand;
    virtual void handle() override
    {
        block->remove_nesting();

        if (block->get_nesting() == 0)
            block->print().reset();
    }
};

struct eof : public ICommand // EOF
{
    using ICommand::ICommand;
    virtual void handle() override
    {
        if (block->get_nesting() == 0)
            block->print().reset();
    }
};
