cmake_minimum_required(VERSION 3.10)
project(mpihm C)

set(CMAKE_C_STANDARD 99)
set(INC_DIR "C:\\Program Files (x86)\\Microsoft SDKs\\MPI\\Include")
set(LIB_DIR "C:\\Program Files (x86)\\Microsoft SDKs\\MPI\\Lib\\x86")

include_directories(${INC_DIR})
link_directories(${LIB_DIR})

add_executable(mpihm main.c)