#include "parallel_accumulate.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(NULL));
    std::vector<int> v;
    const unsigned long n = 100 + std::rand()%100;
    for(unsigned long i=0; i<n; i++) {
        v.push_back(std::rand()%100);
    }
    std::cout << "number of rand: " << n << std::endl;
    // std::cout << accumulate(v.begin(), v.end(), 0) << std::endl;
    std::cout << parallel_accumulate(v.begin(), v.end(), 0) << std::endl;
    return 0;
}
