#include "barrett_mul.h"
#include <iostream>

int main() {
    unsigned char msb = 120;
    unsigned char lsb = 3;
    DoubleInteger<unsigned char> double_i(msb, lsb);
    std::cout << "Msb: " << (unsigned int) double_i.msb 
              << "; Lsb: " << (unsigned int) double_i.lsb 
              << std::endl;
    return 0;
}
