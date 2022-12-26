cmake_minimum_required(VERSION 3.24)
project(simulated_cpu)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(simulated_cpu
        cpu.cpp
        cpu.h
        main.cpp
        mmu.cpp
        mmu.h
        page.cpp
        page.h
        process.cpp
        process.h
        scheduler.cpp
        scheduler.h)
