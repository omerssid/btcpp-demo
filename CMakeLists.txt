CMAKE_MINIMUM_REQUIRED(VERSION 3.5.0)

project(btcpp_demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(behaviortree_cpp)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} BT::behaviortree_cpp)
