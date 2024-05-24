cmake_minimum_required(VERSION 3.22)
project(TicketSystem)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined -fsanitize=leak")
#开o2
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
#add_executable(TicketSystem
#        BPT/LRU.hpp
#        BPT/BPT.hpp
#        BPT/STLSrc/exceptions.hpp
#        BPT/STLSrc/map.hpp
#        BPT/STLSrc/my_print.hpp
#        BPT/STLSrc/my_sort.hpp
#        BPT/STLSrc/utility.hpp
#        BPT/STLSrc/vector.hpp
#        TicketSystem.hpp
#        main.cpp
#        StringFunction.hpp
#        BigBlockBpt.hpp
#        DateAndTimeStruct.hpp
#)
add_executable(code
        BPT/LRU.hpp
        BPT/BPT.hpp
        BPT/STLSrc/exceptions.hpp
        BPT/STLSrc/map.hpp
        BPT/STLSrc/my_print.hpp
        BPT/STLSrc/my_sort.hpp
        BPT/STLSrc/utility.hpp
        BPT/STLSrc/vector.hpp
        TicketSystem.hpp
        main.cpp
        StringFunction.hpp
        BigBlockBpt.hpp
        DateAndTimeStruct.hpp
        HashBPT.hpp
        externalMap.hpp
)
add_executable(testt
        testt.cpp
        externalMap.hpp
)
add_executable(testttt
        testttt.cpp
        timer.hpp
)
