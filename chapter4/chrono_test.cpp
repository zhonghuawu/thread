#include <iostream>

#include <thread>
#include <chrono>

void do_something() {
    std::cout << "wait..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

int main() {
    auto start=std::chrono::high_resolution_clock::now();
    do_something();
    auto finish=std::chrono::high_resolution_clock::now();
    std::cout << "it took "
        << std::chrono::duration<double, std::milli>(finish-start).count()
        << "second." << std::endl;

    return 0;
}
