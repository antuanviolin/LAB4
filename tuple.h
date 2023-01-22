#ifndef LAB4_TUPLE_H
#define LAB4_TUPLE_H
#include <iostream>
#include <tuple>
#include <fstream>

template<typename... T>
std::ostream &operator<<(std::ostream &os, const std::tuple<T...> &tup);

template<size_t n, typename... T>
typename std::enable_if<(n >= sizeof...(T))>::type
print_tuple(std::ostream &, const std::tuple<T...> &) {}

template<size_t n, typename... T>
typename std::enable_if<(n < sizeof...(T))>::type
print_tuple(std::ostream &os, const std::tuple<T...> &tup) {
    if (n != 0)
        os << ", ";
    os << std::get<n>(tup);
    print_tuple<n + 1>(os, tup);
}

template<typename... T>
std::ostream &operator<<(std::ostream &os, const std::tuple<T...> &tup) {
    os << "[";
    print_tuple<0>(os, tup);
    return os << "]";
}

std::string readElem(std::ifstream &file, char delim);

template<typename T>
void getElem(T &ret, std::ifstream &file, char delim);

template<size_t n, typename... T>
typename std::enable_if<(n >= sizeof...(T))>::type
CSVParserHelper(std::tuple<T...> &t, std::ifstream &file, char delim) {}

template<size_t n, typename... T>
typename std::enable_if<(n < sizeof...(T))>::type
CSVParserHelper(std::tuple<T...> &t, std::ifstream &file, char delim) {
    getElem<>(std::get<n>(t), file, delim);
    CSVParserHelper<n + 1>(t, file, delim);
}

template<typename... T>
std::tuple<T...> CSVParser(std::ifstream &file, char delim) {
    std::tuple<T...> tuple;
    CSVParserHelper<0>(tuple, file, delim);
    return tuple;
}

#endif //LAB4_TUPLE_H
