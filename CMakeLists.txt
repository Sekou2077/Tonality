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

# Find FFTW3 package
find_package(FFTW3 CONFIG REQUIRED)


# Link against PortAudio and FFTW3 libraries
target_link_libraries(Tonality PRIVATE portaudio FFTW3::fftw3)

