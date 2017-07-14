#ifndef __FUNC_H__
#define __FUNC_H__
#include <iostream>

void do_something(int& i) {
    std::cout << i++ << std::endl;
}

struct func {
    int& i;
    func(int& _i) : i(_i) {}
    
    void operator()() {
        for(unsigned j=0; j<10; ++j) {
            do_something(i);
        }
    }
};

#endif
