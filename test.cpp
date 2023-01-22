#include <gtest/gtest.h>
#include "tuple.h"
#include <fstream>

struct paramList1 {
    std::string inpath;
    char delim;
    int integ;
    double doubl;
    char symb;
    std::string str;
};


class paramTestReadCVS : public ::testing::TestWithParam<paramList1> {
};

TEST_P(paramTestReadCVS, test1) {
    std::string inpath = GetParam().inpath;
    std::ifstream finput;
    finput.open(inpath);
    char delim = GetParam().delim;
    int integ = GetParam().integ;
    double doubl = GetParam().doubl;
    char symb = GetParam().symb;
    std::string str = GetParam().str;
    auto tuple = CSVParser<int, double, char, std::string>(finput, delim);
    bool allRight = true;
    if(std::get<0>(tuple) != integ){
            allRight = false;
    } else if (std::get<1>(tuple) != doubl){
        allRight = false;
    } else if (std::get<2>(tuple) != symb){
        allRight = false;
    }else if (std::get<3>(tuple) != str){
        allRight = false;
    }
    EXPECT_TRUE(allRight);
}

INSTANTIATE_TEST_CASE_P

(paramTestReadCVS, paramTestReadCVS, testing::Values(
        paramList1{"test1.txt", ',', 1, 123.34, '!', "cdf"},
        paramList1{"test2.txt", '!', 2421, 0.34, '#', "hello"}));