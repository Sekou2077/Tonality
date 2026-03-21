# CMakeLists.txt for the project

# Minimum CMake version required
cmake_minimum_required(VERSION 3.16)

# Project name 
project(Tonality LANGUAGES CXX)


# Add the executable target
add_executable(Tonality src/main.cpp
                    src/Audio_processing/Music_input.cpp
                    src/Audio_processing/Dsp.cpp)

# find PortAudio package
find_package(portaudio CONFIG REQUIRED)

# Set the CMake module path to include the directory where the findfftw.cmake module is located
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/CMake/Modules/findfftw")

# Find FFTW3 float package
find_package(FFTW REQUIRED COMPONENTS FLOAT_LIB)


# Link against PortAudio and FFTW3 libraries
target_link_libraries(Tonality PRIVATE portaudio FFTW::Float)

