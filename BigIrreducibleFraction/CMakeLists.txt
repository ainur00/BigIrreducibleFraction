cmake_minimum_required(VERSION 3.0)
project(BigInteger)
set(SOURCES sourceFiles/main.cpp)
include_directories("headerFiles")
add_executable(mainDemonstration ${SOURCES})
