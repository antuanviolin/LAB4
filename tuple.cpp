#include "tuple.h"

std::string readElem(std::ifstream &file, char delim, char delimRow) {
    std::string elem;
    char buffer;
    while (true) {
        file.get(buffer);
        if (buffer == delim || buffer == delimRow || file.eof()) {
            break;
        }
        elem += buffer;
    }
    return elem;
}

template<>
void getElem(int &ret, std::ifstream &file, char delim, char delimRow) {
    std::string elem = readElem(file, delim, delimRow);
    try {
        size_t pos;
        ret = stoi(elem, &pos);
        }
    catch (const std::invalid_argument&) {
            throw tupleException("Wrong type");
        }
}

template<>
void getElem(std::string &ret, std::ifstream &file, char delim, char delimRow) {
    std::string elem = readElem(file, delim, delimRow);
    ret = elem;
}

template<>
void getElem(double &ret, std::ifstream &file, char delim, char delimRow) {
    std::string elem = readElem(file, delim, delimRow);
    try {
        size_t pos;
        ret = stod(elem, &pos);
    }
    catch (const std::invalid_argument&) {
        throw tupleException("Wrong type");
    }
}

template<>
void getElem(char &ret, std::ifstream &file, char delim, char delimRow) {
    std::string elem = readElem(file, delim, delimRow);
    ret = elem[0];
}