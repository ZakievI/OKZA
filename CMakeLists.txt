cmake_minimum_required(VERSION 3.15)
project(OKZA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Путь к заголовкам fcalc.h и библиотеке fcalc.dll
set(FCALC_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/resourse")
set(FCALC_DLL "${CMAKE_SOURCE_DIR}/resourse/fcalc.dll")

add_subdirectory(lib/unit0)
# add_subdirectory(lib/unit1)
# add_subdirectory(lib/unit2)
# add_subdirectory(lib/unit3)
# add_subdirectory(lib/unit4)
# add_subdirectory(lib/unit5)
# add_subdirectory(lib/unit6)
# add_subdirectory(lib/unit7)
# add_subdirectory(lib/unit8)
add_subdirectory(lib/unit9)
# add_subdirectory(lib/unit10)

# Основной исполняемый файл (main.cpp)
add_executable(okza_main main.cpp)

target_link_libraries(okza_main PRIVATE
                     unit0
                     unit9
                     )

if(WIN32)
    add_custom_command(
        TARGET okza_main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/resourse/"
            "$<TARGET_FILE_DIR:okza_main>/resourse/"
    )
endif()