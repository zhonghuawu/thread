#include <iostream>
#include <thread>
#include <string>

void f(int& i, const std::string& s) {
    std::cout << "i = " << ++i << std::endl;
    std::cout << "s = " << s << std::endl;
}

void oops(int some_param) {
    int i = 3;
    std::thread t(f, std::ref(i), "hello");
    t.join();
    std::cout << "current i = " << i << std::endl;
}

int main() {
    oops(1);
    return 0;
}
