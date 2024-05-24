//
// Created by qiuyuhang on 24-5-24.
//
#include "externalMap.hpp"
int main() {
    externalMap<int, int> aa("what");
    for (int i = 0; i < 100; ++i) {
        aa.insert(i, i+1);
    }
    for (int i = 0; i < 100; ++i) {
        std::cout<<aa.find3(i)[0]<<std::endl;
    }
    for (int i = 0; i < 50; ++i) {
        aa.delete_(i);
    }
    return 0;
}