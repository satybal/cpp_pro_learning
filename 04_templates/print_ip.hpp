#include <iostream>
#include <cmath>
#include <bitset>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

/*!
    * Converts 8-bit number to decimal
*/
int byte_to_decimal(const char* number) {
    auto result = 0;

    for (size_t i{}; i < 8; ++i) {
        if (number[i] == '1') 
            result += pow(2, 7 - i);
    }

    return result;
}

/*!
    * Converts binary string byte by byte to decimals
    * and prints with '.' separator
*/
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
    template < typename T >
    struct is_container : false_type {};

    template < typename T, typename Alloc >
    struct is_container<vector<T, Alloc>> : true_type {};

    template < typename T, typename Alloc >
    struct is_container<list<T, Alloc>> : true_type {};
} // _container

namespace _tuple {
    template <typename T>
    struct is_tuple : false_type {};

    template <typename ...Args>
    struct is_tuple<tuple<Args...>> : true_type {};

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

/*!
    * Template function for integral types
*/
template <class T>
enable_if_t<is_integral<T>::value, void>
print_ip(const T& value)
{
    string binary = bitset<sizeof(value) * 8>(value).to_string();
    print_binary(binary);
}

/*!
    * Template function for containers
*/
template<typename T>
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

/*!
    * Template function for strings
*/
template <class T>
enable_if_t<is_same_v<T, string>, void>
print_ip(const T& value) {
    cout << value << endl;
}

/*!
    * Template function for tuples
*/
template<class T>
enable_if_t<_tuple::is_tuple<T>::value, void>
print_ip(const T& value) {
    _tuple::print_tuple(value);
    cout << endl;
}