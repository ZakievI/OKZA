file(GLOB SOURCES "source/*.cpp")
file(GLOB HEADERS "include/*.h")

add_library(unit0 STATIC ${SOURCES} ${HEADERS})

target_include_directories(unit0 PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${FCALC_INCLUDE_DIR}  
)

if(WIN32)
    target_compile_definitions(unit0 PRIVATE "FCALC_API=__stdcall")
endif()