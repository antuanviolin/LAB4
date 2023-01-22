#include <iostream>
#include "tuple.h"
#include <gtest/gtest.h>

int main() {
    std::ifstream file;
    file.open("file.txt");
    if(!file.is_open()){
        std::cout<<"File not found";
    } else{
        auto tuple = CSVParser<int, double, char, std::string>(file, ',', '\n');
        for (int i = 0; i < tuple.size(); ++i){
            std::cout << tuple[i] << std::endl;
        }
    }
    /*printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();*/
}
