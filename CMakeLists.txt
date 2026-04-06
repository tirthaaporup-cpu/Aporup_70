cmake_minimum_required(VERSION 3.10)
project(SFML_Assignment)

set(SFML_DIR "/opt/homebrew/lib/cmake/SFML")
find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)

# Task 101 - The Static Circle
add_executable(task101 task101.cpp)
target_link_libraries(task101 SFML::Graphics SFML::Window SFML::System)

# Task 102 - The Growing Circle
add_executable(task102 task102.cpp)
target_link_libraries(task102 SFML::Graphics SFML::Window SFML::System)

# Task 103 - The Bouncing Circle
add_executable(task103 task103.cpp)
target_link_libraries(task103 SFML::Graphics SFML::Window SFML::System)