cmake_minimum_required(VERSION 3.22)
project(TicketSystem)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined -fsanitize=leak")
#开o2
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
add_executable(code
        src/BPT/LRU.hpp
        src/BPT/BPT.hpp
        src/BPT/STLSrc/exceptions.hpp
        src/BPT/STLSrc/map.hpp
        src/BPT/STLSrc/my_print.hpp
        src/BPT/STLSrc/my_sort.hpp
        src/BPT/STLSrc/utility.hpp
        src/BPT/STLSrc/vector.hpp
        src/StringFunction.hpp
        src/BigBlockBpt.hpp
        src/DateAndTimeStruct.hpp
        src/HashBPT.hpp
        src/externalMap.hpp
        src/timer.hpp
        TicketSystem.hpp
        main.cpp
)

