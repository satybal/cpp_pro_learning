#include "ip_filter.hpp"

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void reverse_sort(std::vector<std::vector<std::string>>& pool) {
    std::sort(
        pool.begin(), 
        pool.end(), 
        [&](std::vector<std::string> left, std::vector<std::string> right) {
            return (
                (
                    std::stoi(left[0]) > std::stoi(right[0])
                ) || (
                    left[0] == right[0] && 
                    std::stoi(left[1]) > std::stoi(right[1])
                ) || (
                    left[0] == right[0] && 
                    left[1] == right[1] && 
                    std::stoi(left[2]) > std::stoi(right[2])
                ) || (
                    left[0] == right[0] && 
                    left[1] == right[1] && 
                    left[2] == right[2] && 
                    std::stoi(left[3]) > std::stoi(right[3])
                )
            );
        }
    );
}

void print_ip(std::vector<std::string>& line) {
    for (auto& num: line) {
        std::cout << num;

        if (&num != &line.back())
            std::cout << ".";
    }
    std::cout << std::endl;
}

// int main(int argc, char const *argv[]) {

//     std::ifstream in_file {"ip_filter.tsv"};
//     if (!in_file.is_open()) {
//         std::cout << "Failed to open file ip_filter.tsv!" << std::endl;
//         return -1;
//     }

//     try
//     {
//         std::vector<std::vector<std::string>> ip_pool;

//         for(std::string line; std::getline(in_file, line);)
//         {
//             std::vector<std::string> v = split(line, '\t');
//             ip_pool.push_back(split(v.at(0), '.'));
//         }

//         // Reverse sort
//         reverse_sort(ip_pool);

//         // Sorted output
//         for(auto& ip: ip_pool) {
//             print_ip(ip);
//         }

//         // Print where first number is 1
//         for (auto& ip: ip_pool) {
//             if (ip[0] == "1") 
//                 print_ip(ip);
//         }

//         // Print where first is 46 and the second is 70
//         for (auto& ip: ip_pool) {
//             if (ip[0] == "46" && ip[1] == "70") 
//                 print_ip(ip);
//         }

//         // Print if any is 46
//         for (auto& ip: ip_pool) {
//             bool flag {false};
//             for (auto& part: ip) {
//                 if (part == "46") {
//                     flag = true;
//                     break;
//                 }
//             }
//             if (flag) 
//                 print_ip(ip);
//         }
//     }
//     catch(const std::exception &e)
//     {
//         std::cerr << e.what() << std::endl;
//     }

//     return 0;
// }
