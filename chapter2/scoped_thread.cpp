#include "func.h"

#include <thread>

class scoped_thread {
    std::thread t;
public :
    explicit scoped_thread(std::thread _t) : t(std::move(_t)) {
        std::cout << "scoped_thread constructor" << std::endl;
        if(!t.joinable())
            throw std::logic_error("No thread");
    }
    ~scoped_thread() {
        std::cout << "scoped_thread destroy" << std::endl;
        t.join();
    }

    scoped_thread(const scoped_thread& )=delete;
    scoped_thread& operator=(const scoped_thread& )=delete;
};

struct func;

void f() {
    int some_local_state = 4;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    // my_thread.join();
    try {
        scoped_thread t(std::move(my_thread));
    } catch (const std::logic_error& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << __FILE__ << " " << __LINE__ << std::endl;
}

int main() {
    f();
    return 0;
}
