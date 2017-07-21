#include "parallel_quick_sort.h"
#include "sequential_quick_sort.h"

#include <iostream>
#include <list>
#include <algorithm>

#include <chrono>

template<typename Func, typename T=int>
std::chrono::duration<double, std::milli> test_func(Func quick_sort, std::list<T> input) {
    auto start=std::chrono::high_resolution_clock::now();
    auto result = quick_sort(input);
    auto finish=std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(finish-start);
}

int main() {
    const int N = 200000;
    auto gen=[N](){ return rand()%N; };
    std::list<int> input;
    std::generate_n(back_inserter(input), N, gen);

    auto dura=test_func(sequential_quick_sort<int>, input);
    std::cout << "sequential_quick_sort took " << dura.count() << " seconds " << std::endl;

    dura=test_func(parallel_quick_sort<int>, input);
    std::cout << "parallel_quick_sort took " << dura.count() << " seconds" << std::endl;
    
    return 0;
}
