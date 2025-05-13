cmake_minimum_required(VERSION 3.10)

# Project name and version
project(okza_main VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCES
    main.cpp
    lib/unit0/source/test_unit0.cpp
    lib/unit9/source/test_unit9.cpp
    resourse/fcalc.cpp              # Добавляем реализацию fcalc
)

# Add executable
add_executable(okza_main ${SOURCES})

# Add include directories for this target
target_include_directories(okza_main PRIVATE
    ${PROJECT_SOURCE_DIR}/lib/unit0/include
    ${PROJECT_SOURCE_DIR}/lib/unit9/include
    ${PROJECT_SOURCE_DIR}/resourse
)

# Copy DLL to build directory so the executable can load it at runtime
file(COPY ${PROJECT_SOURCE_DIR}/resourse/fcalc.dll
     DESTINATION ${CMAKE_BINARY_DIR})
