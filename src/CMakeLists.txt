cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 11)
project(overlay)

find_package(OpenCV REQUIRED)
add_executable(${PROJECT_NAME} overlay.cpp functions.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
