#ifndef LAB4_TUPLE_H
#define LAB4_TUPLE_H
#include <iostream>
#include <tuple>
#include <vector>
#include <fstream>

class tupleException : public std::exception {
public:
    explicit tupleException(std::string error) : error_(std::move(error)) {}

    const char *what() const noexcept override { return error_.c_str(); }

private:
    std::string error_;
};

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

std::string readElem(std::ifstream &file, char delim, char delimRow);

template<typename T>
void getElem(T &ret, std::ifstream &file, char delim, char delimRow);

template<size_t n, typename... T>
typename std::enable_if<(n >= sizeof...(T))>::type
CSVParserHelper(std::tuple<T...> &t, std::ifstream &file, char delim, char delimRow) {}

template<size_t n, typename... T>
typename std::enable_if<(n < sizeof...(T))>::type
CSVParserHelper(std::tuple<T...> &t, std::ifstream &file, char delim, char delimRow) {
    getElem<>(std::get<n>(t), file, delim, delimRow);
    CSVParserHelper<n + 1>(t, file, delim, delimRow);
}

template<typename... T>
std::vector<std::tuple<T...>> CSVParser(std::ifstream &file, char delim, char delimRow) {
    std::vector<std::tuple<T...>> tuples;
    while (true) {
        if (file.eof()) {
            break;
        }
        std::tuple<T...> tuple;
        CSVParserHelper<0>(tuple, file, delim, delimRow);
        tuples.push_back(tuple);
    }
    return tuples;
}

#endif //LAB4_TUPLE_H
