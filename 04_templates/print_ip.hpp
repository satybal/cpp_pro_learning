#include <iostream>
#include <cmath>
#include <bitset>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int byte_to_decimal(const char* number) {
    auto result = 0;

    for (size_t i{}; i < 8; ++i) {
        if (number[i] == '1') 
            result += pow(2, 7 - i);
    }

    return result;
}

void print_binary(const string& binary) {
    cout << byte_to_decimal(binary.substr(0, 8).c_str());

    size_t pos = 8;
    while (pos < binary.size()) {
        cout << '.' << byte_to_decimal(binary.substr(pos, 8).c_str());
        pos += 8;
    }

    cout << endl;
}

namespace _container {
    template <typename T>
    struct is_container: false_type {};

    template <typename T, typename Alloc>
    struct is_container<vector<T, Alloc>>: true_type {};

    template <typename T, typename Alloc>
    struct is_container<list<T, Alloc>>: true_type {};
} // _container

namespace _tuple {
    template <size_t i = 0, typename ...T>
    typename enable_if< i == sizeof...(T), void >::type
    print_tuple(const tuple<T...>&) {}

    template <size_t i = 0, typename ...T>
    typename enable_if< (i < sizeof...(T)), void >::type
    print_tuple(const tuple<T...>& t) {
        i == 0 ? cout << get<i>(t) : cout << "." << get<i>(t);
        print_tuple< i + 1, T... >(t);
    }
} // _tuple

// numbers
template <class T>
enable_if_t<std::is_integral<T>::value, void>
print_ip(const T& value)
{
    string binary = bitset<sizeof(value) * 8>(value).to_string();
    print_binary(binary);
}

// containers
template <class T>
enable_if_t<_container::is_container<T>::value, void>
print_ip(const T& value) {
    if (!value.empty()) {
        cout << *value.begin();
        for_each(next(value.begin()), value.end(), [] (auto& val) {
            cout << "." << val;
        });
        cout << endl;
    }
}

// string
template <class T>
enable_if_t<is_same_v<T, string>, void>
print_ip(const T& value) {
    cout << value << endl;
}

// tuple
template<class... Args>
void print_ip(const tuple<Args...>& value) {
     _tuple::print_tuple(value);
    cout << endl;
}