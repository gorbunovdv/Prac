cmake_minimum_required(VERSION 3.3)

project(helloqt)

set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -std=c++14")
set(SOURCE_FILES catalog.cpp main.cpp radioprogram.cpp requestsgenerator.cpp royalmanager.cpp simulator.cpp statistics.cpp events.cpp structures.cpp)

#find_package(Qt5Widgets REQUIRED)
add_executable(main ${SOURCE_FILES})
#target_link_libraries(main Qt5::Widgets)