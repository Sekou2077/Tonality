# CMakeLists.txt for the project

# Minimum CMake version required
cmake_minimum_required(VERSION 3.16)

# Project name 
project(Tonality LANGUAGES CXX)


# Add the executable target
add_executable(Tonality Music_input.cpp)

# find PortAudio package
find_package(portaudio CONFIG REQUIRED)


# Link against PortAudio
target_link_libraries(Tonality PRIVATE portaudio)

