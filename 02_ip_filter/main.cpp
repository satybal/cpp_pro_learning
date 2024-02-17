#include <fstream>
#include "ip_filter.hpp"

int main(int, char **) {
    try
    {
        std::vector<std::vector<std::string>> ip_pool;
        std::string line;

        while (std::getline(std::cin, line))
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // Reverse sort
        reverse_sort(ip_pool);
        
        // Sorted output
        for(auto& ip: ip_pool) {
            print_ip(ip);
        }

        // Print where first number is 1
        for (auto& ip: ip_pool) {
            if (ip[0] == "1") 
                print_ip(ip);
        }

        // Print where first is 46 and the second is 70
        for (auto& ip: ip_pool) {
            if (ip[0] == "46" && ip[1] == "70") 
                print_ip(ip);
        }

        // Print if any is 46
        for (auto& ip: ip_pool) {
            bool flag {false};
            for (auto& part: ip) {
                if (part == "46") {
                    flag = true;
                    break;
                }
            }
            if (flag) 
                print_ip(ip);
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
