#include "../src/include/barrett_mul.h"
#include <vector>
#include <iostream>

template <UnsignedInteger T>
T sum_vector(std::vector<T>& v) {
    T sum = 0;
    for (auto x: v) {
        sum += x;
    }
    return sum;
}

int main() {
    std::vector<char> v {0, 1, 2, 3, 4, 5};
    char sum = sum_vector(v);
    for (unsigned int i=0; i+1 < v.size(); i++) {
        std::cout << (int) v[i] << " + ";
    }
    std::cout << (int) v[v.size()-1] << " = " << (int) sum << std::endl;
    return 0;
}