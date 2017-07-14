#include <iostream>

#include <algorithm>
#include <list>

#include <thread>
#include <mutex>

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value) {
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(new_value);
}

bool list_contains(int value_to_find) {
    std::lock_guard<std::mutex> guard(some_mutex);
    return std::find(some_list.begin(), some_list.end(), value_to_find)!=some_list.end();
}

int main() {
    for(int i=0; i<10; ++i)
        some_list.push_back(i);
    std::thread t1(add_to_list, 30);
    std::thread t2(list_contains, 30);
    t1.join();
    t2.join();
    return 0;
}
