#include "allocator.hpp"
#include <vector>

int main(int, char**)
{

    std::vector<int> vec;
    std::vector<int, MyAllocator<int>> custom_vec;
    return 0;
}