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

std::string readElem(std::ifstream &file, char delim) {
    std::string elem;
    char buffer;
    while (true) {
        file.get(buffer);
        std::cout<<buffer<<std::endl;
        if (buffer == delim || buffer == '\n' || file.eof()) {
            break;
        }
        elem += buffer;
    }
    return elem;
}

template<typename T>
void getElem(T &ret, std::ifstream &file, char delim) {}

template<>
void getElem(int &ret, std::ifstream &file, char delim) {
    std::string elem = readElem(file, delim);
    ret = std::stoi(elem);
}

template<>
void getElem(std::string &ret, std::ifstream &file, char delim) {
    std::string elem = readElem(file, delim);
    ret = elem;
}

template<>
void getElem(double &ret, std::ifstream &file, char delim) {
    std::string elem = readElem(file, delim);
    ret = std::stod(elem);
}

template<>
void getElem(char &ret, std::ifstream &file, char delim) {
    std::string elem = readElem(file, delim);
    ret = elem[0];
}

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


int main() {
    std::ifstream file;
    file.open("C:\\Users\\violi\\CLionProjects\\lab4\\file.txt");
    auto tuple = CSVParser<int, double, int, std::string>(file, '!');
    std::cout << tuple << std::endl;
    return 0;
}
