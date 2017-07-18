#include "threadsafe_queue.h"

#include <iostream>

#include <cstdlib>
#include <ctime>

#include <thread>

bool flag = true;

void push_value(threadsafe_queue<int>& tq) {
    int value = 0;
    while((value=rand()%100)!=0) {
        std::mutex m;
        std::lock_guard<std::mutex> lk(m);
        std::cout << "push " << value << std::endl;
        tq.push(value);
    }
    flag = false;
}

void pop_value(threadsafe_queue<int>& tq) {
    std::shared_ptr<int> res;
    while(flag) {
        std::mutex m;
        std::lock_guard<std::mutex> lk(m);
        res = tq.wait_and_pop();
        std::cout << "pop " << *res << std::endl;
    }
}

int main() {
    threadsafe_queue<int> tq;
    std::thread pop_thread(pop_value, std::ref(tq));
    std::thread push_thread(push_value, std::ref(tq));
    std::cout << "main thread: start testing..." << std::endl;
    push_thread.join();
    pop_thread.join();
    std::cout << "main thread: end testing..." << std::endl;

    return 0;
}
