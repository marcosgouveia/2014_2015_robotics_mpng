cmake_minimum_required(VERSION 2.8)
project(obstacle_avoidance_example)

# set and find webots environment paths
set(WEBOTS_HOME /usr/local/webots)
find_library(CPP_CONTROLLER_LIBRARY CppController ${WEBOTS_HOME}/lib)
find_library(C_CONTROLLER_LIBRARY Controller ${WEBOTS_HOME}/lib)

# add include paths to link
add_definitions(-I${WEBOTS_HOME}/include/controller/cpp -I${WEBOTS_HOME}/include -Wall -I${WEBOTS_HOME}/include/controller/c -DLINUX)

# add main executable
add_executable(obstacle_avoidance_example obstacle_avoidance_example.cpp MyRobot.cpp)

# link to libraries
target_link_libraries(obstacle_avoidance_example ${C_CONTROLLER_LIBRARY} ${CPP_CONTROLLER_LIBRARY} m)
