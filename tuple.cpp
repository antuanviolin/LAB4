#include "tuple.h"

std::string readElem(std::ifstream &file, char delim) {
    std::string elem;
    char buffer;
    while (true) {
        file.get(buffer);
        if (buffer == delim || buffer == '\n' || file.eof()) {
            break;
        }
        elem += buffer;
    }
    return elem;
}

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