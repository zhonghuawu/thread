#include <iostream>
#include <string>
#include <future>
#include <chrono>

int main() {
    std::future<int> f1 = std::async([]{ return 9; });
    std::cout << f1.get() << std::endl;

    std::future<void> f2 = std::async([]{ std::cout << 8 << std::endl; });
    f2.wait();

    std::future<int> f3 = std::async(std::launch::async, 
            []{ std::this_thread::sleep_for(std::chrono::seconds(3));
            return 7; 
            });
    std::future_status status;
    std::cout << "wait..." << std::endl;
    do {
        status = f3.wait_for(std::chrono::seconds(1));
        if(status == std::future_status::deferred) {
            std::cout << "deferred..." << std::endl;
        }
        else if(status == std::future_status::timeout) {
            std::cout << "timeout..." << std::endl;
        }
       else if(status == std::future_status::ready) {
            std::cout << "ready..." << std::endl;
        }
    } while(status != std::future_status::ready);

    std::cout << "result is " << f3.get() << std::endl;
    return 0;
}
