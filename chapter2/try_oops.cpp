#include <iostream>
#include <thread>

#include "func.h"

struct func;

// 等待线程结束
void f() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    try {
        std::cout << __FILE__ << std::endl;
    } catch (...) {
        my_thread.join();
        throw;
    }
    my_thread.join();
}

int main() {
    f();
    return 0;
}
