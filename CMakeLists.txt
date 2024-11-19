cmake_minimum_required(VERSION 3.29)
project(servtest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS system asio)

add_executable(servtest main.cpp)

target_link_libraries(servtest PRIVATE Boost::system Boost::asio Ws2_32)