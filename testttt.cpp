
#include "timer.hpp"
#include <iostream>
int main() {
    Timer timer("test");
    timer.start();
    int a=0;
    for (int i = 0; i < 10000; ++i) {
        std::cout<<i;
//        a++;
    }
    timer.stop();
    return 0;
}