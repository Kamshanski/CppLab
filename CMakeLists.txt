cmake_minimum_required(VERSION 3.20)
project(Lab)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-g")

add_executable(Test main.cpp)
add_executable(Lab1_1 Lab1/Lab1_1.cpp)
add_executable(Lab1_2 Lab1/Lab1_2.cpp)
add_executable(Lab1_3 Lab1/Lab1_3.cpp)
add_executable(Lab1_4 Lab1/Lab1_4.cpp)

add_executable(Lab2_1 Lab2/Lab2_1.cpp)
add_executable(Lab2_2 Lab2/Lab2_2.cpp)
add_executable(Lab2_3 Lab2/Lab2_3.cpp)
add_executable(Lab2_4 Lab2/Lab2_4.cpp)

add_executable(Lab3_1 Lab3/Lab3_1.cpp)
add_executable(Lab3_2 Lab3/Lab3_2.cpp)
add_executable(Lab3_3 Lab3/Lab3_3.cpp)
add_executable(Lab3_4 Lab3/Lab3_4.cpp)

add_executable(Lab4_1 Lab4/Lab4_1.cpp)
add_executable(Lab4_2 Lab4/Lab4_2.cpp)
add_executable(Lab4_3 Lab4/Lab4_3.cpp)
add_executable(Lab4_4 Lab4/Lab4_4.cpp)

add_executable(Lab5_1 Lab5/Lab5_1.cpp)
add_executable(Lab5_2 Lab5/Lab5_2.cpp)
add_executable(Lab5_3 Lab5/Lab5_3.cpp)
add_executable(Lab5_4 Lab5/Lab5_4.cpp)

add_executable(Lab6_1 Lab6/Lab6_1.cpp)
add_executable(Lab6_2and5 Lab6/Lab6_2_5.cpp)
add_executable(Lab6_3 Lab6/Lab6_3.cpp)
add_executable(Lab6_4 Lab6/Lab6_4.cpp)

add_executable(Lab7 Lab7/Lab7.cpp)

add_executable(Lab8_1 Lab8/Lab8_1.cpp)
add_executable(Lab8_2 Lab8/Lab8_2.cpp)
add_executable(Lab8_3 Lab8/Lab8_3.cpp)
add_executable(Lab8_4 Lab8/Lab8_4.cpp)
add_executable(Lab8_5 Lab8/Lab8_5.cpp)

add_executable(Lab9_1 Lab9/Lab9_1.cpp)
add_executable(Lab9_2 Lab9/Lab9_2.cpp)
add_executable(Lab9_3 Lab9/Lab9_3.cpp)
add_executable(Lab9_4 Lab9/Lab9_4.cpp)
add_executable(Lab9_5 Lab9/Lab9_5.cpp)

add_executable(Lab10_1 Lab10/Lab10_1.cpp)
add_executable(Lab10_2 Lab10/Lab10_2.cpp)
add_executable(Lab10_3 Lab10/Lab10_3.cpp)
add_executable(Lab10_4 Lab10/Lab10_4.cpp)

add_executable(Lab11_1 Lab11/Lab11_1.cpp)
add_executable(Lab11_2 Lab11/Lab11_2.cpp)
add_executable(Lab11_3 Lab11/Lab11_3.cpp)
add_executable(Lab11_4 Lab11/Lab11_4.cpp)
add_executable(Lab11_5 Lab11/Lab11_5.cpp)

add_executable(Lab12_1 Lab12/Lab12_1.cpp)
add_executable(Lab12_2 Lab12/Lab12_2.cpp)
add_executable(Lab12_3 Lab12/Lab12_3.cpp)
add_executable(Lab12_4 Lab12/Lab12_4.cpp)

add_executable(Lab13 Lab13/Lab13.cpp)

add_executable(Lab14 Lab14/Lab14.cpp)

add_executable(Lab15 Lab15/Lab15.cpp)

add_executable(Lab16_1 Lab16/Lab16_1.cpp)
add_executable(Lab16_2 Lab16/Lab16_2.cpp)


add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(GTest LibraryTests.cpp)
target_link_libraries(GTest gtest gtest_main)
target_link_libraries(GTest gmock gmock_main)

