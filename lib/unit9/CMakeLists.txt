file(GLOB SOURCES "source/*.cpp")
file(GLOB HEADERS "include/*.h")

add_library(unit9 STATIC ${SOURCES} ${HEADERS})

target_include_directories(unit9 PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Если модуль зависит от других библиотек (например, unit1)
# target_link_libraries(unit0 PRIVATE unit1)