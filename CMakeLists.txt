cmake_minimum_required(VERSION 3.10)

# Project name and version
project(MyProject VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/lib/unit0/include
    ${PROJECT_SOURCE_DIR}/lib/unit9/include
    ${PROJECT_SOURCE_DIR}/resourse
)

# Add source files
set(SOURCES
    main.cpp
    lib/unit0/source/test_unit0.cpp
    lib/unit9/source/test_unit9.cpp
)

# Add executable
add_executable(okza_main ${SOURCES})

# If you want to link fcalc.dll at runtime, you can optionally copy it to the build directory
file(COPY ${PROJECT_SOURCE_DIR}/resourse/fcalc.dll
     DESTINATION ${CMAKE_BINARY_DIR})
