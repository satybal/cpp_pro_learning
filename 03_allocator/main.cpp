#include <iostream>
#include <map>
#include "allocator.hpp"
#include "container.hpp"


template <class T>
T& fill_map(T& _map) {
    for (auto i = 0; i < 10; ++i) {
        if (i == 0) 
            _map[i] = 1;
        else 
            _map[i] = _map[i-1] * i;
    }
    return _map;
}

template <class T>
void print_map(T& _map) {
    for (auto &[key, value]: _map) {
        std::cout << key << " " << value << std::endl;
    }
    std::cout << std::endl;
}

int main() {

    std::map<int, int> custom_map;
    std::map<int, int, std::less<int>, Allocator<std::pair<const int, int>, 10>> pool_map;

    std::cout << "## Custom map content" << std::endl;
    print_map(fill_map(custom_map));

    std::cout << "## Pool map content" << std::endl;
    print_map(fill_map(pool_map));

    std::cout << "## Simple vector with std::allocator" << std::endl;
    Container<int, 10> con1;
    for (auto i = 0; i < 10; ++i) 
        con1.push_back(i);
    for (auto i = 0; i < 10; ++i) 
        std::cout << con1[i] << " ";;
    std::cout << std::endl << std::endl;

    std::cout << "## Simple vector with pool allocator" << std::endl;
    Container<int, 10, Allocator<int, 10>> con;
    for (auto i = 0; i < 10; ++i) 
        con.push_back(i);
    for (auto i = 0; i < 10; ++i) 
        std::cout << con[i] << " ";;
    std::cout << std::endl;

    return 0;
}