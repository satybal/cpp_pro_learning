#include <iostream>
#include "handler.hpp"
#include <unistd.h>


int main(int, const char** argv)
{
    Handler handler(argv[1]);
    std::string line;

    while (true)
    {
        std::getline(std::cin, line);
        std::cout << line << std::endl;
        handler.send(line);

        if (std::cin.eof())
        {
            auto empty = std::string("");
            handler.send(empty);
            break;
        }

        sleep(1);
    }

    return 0;
}