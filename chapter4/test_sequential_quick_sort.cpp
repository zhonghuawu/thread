#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

#include "sequential_quick_sort.h"
#include "parallel_quick_sort.h"

int main() {
    const int n = 20;
    auto gen=[n](){ return rand()%n; };
    std::list<int> input;
    std::generate_n(back_inserter(input), 20, gen);
    std::copy(input.begin(), input.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    // std::list<int> result = sequential_quick_sort(input);
    std::list<int> result = parallel_quick_sort(input);
    std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}

