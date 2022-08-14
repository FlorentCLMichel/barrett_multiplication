/**
 * @file
 * @brief test of the `log_2` function on all positive integers below 2^16
 */

#include "barrett_mul.h"
#include <cmath>

int main() {
    std::cout << "Running test LOG_2_U16... " << std::flush;
    for (unsigned int i = 1; i < (1 << 16); i++) {
        unsigned int j = log_2(i);
        if (j != ceil(log2(i))) {
            std::cout << "FAILED: " 
                      << " ceil(log_2(" << i << ")) != " << j
                      << std::endl;
            return 1;
        }
    }
    std::cout << "PASSED" << std::endl;
    return 0;
}
