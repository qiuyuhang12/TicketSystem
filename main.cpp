#include <iostream>
#include "TicketSystem.hpp"
int main() {
//    关同步流
    std::ios::sync_with_stdio(false);
//    关缓冲区
    std::cin.tie(0);
    std::cout.tie(0);
//    clearFile();
    TicketSystem ticketSystem;
    ticketSystem.run();
    return 0;
}

