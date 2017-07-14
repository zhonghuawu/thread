#include <iostream>
#include <thread>

#include "func.h"

struct func;

// 当线程仍然访问局部变量时返回的函数
void oops() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.join();
}

int main() {
    oops();
    return 0;
}
