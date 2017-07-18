#include <future>
#include <iostream>

#include <chrono>

// 使用 std::future 获取异步任务的返回值

int find_the_answer_to_ltuae();
void do_other_stuff();

int main() {
    std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
    do_other_stuff();
    std::cout << "The answer is " << the_answer.get() << std::endl;
    return 0;
}


int find_the_answer_to_ltuae() {
    return 20;
}

void do_other_stuff() {
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(4));
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> dura = end-start;
    std::cout << "wait for " << dura.count() << "ms." << std::endl;
}
