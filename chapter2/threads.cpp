#include <iostream>
#include <thread>

#include <vector>
#include <algorithm>

void do_work(unsigned id) {
    std::cout << "thread " << id << std::endl;
}

void f() {
    std::vector<std::thread> threads;
    for(unsigned i=0; i<20; ++i) {
        threads.push_back(std::thread(do_work, i));
    }
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}

int main() {
    f();
    return 0;
}
