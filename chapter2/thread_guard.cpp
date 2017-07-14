#include <iostream>
#include <thread>

#include "func.h"

// 使用RAII等待线程完成

class thread_guard {
    std::thread& t;
public :
    explicit thread_guard(std::thread& _t) : t(_t) {}
    ~thread_guard() {
        if(t.joinable())
            t.join();
    }
    thread_guard(const thread_guard& )=delete;
    thread_guard& operator=(const thread_guard& )=delete;
};

struct func;

void f() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    thread_guard g(my_thread);

    std::cout << __FILE__ << std::endl;
}

int main() {
    f();
    return 0;
}
