cmake_minimum_required(VERSION 3.20)
project(pendulum C)

set(CMAKE_C_STANDARD 11)

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${SOURCES} include/sim.h src/sim.c)

if(WIN32)
    target_link_libraries(
        pendulum PUBLIC
        "${PROJECT_SOURCE_DIR}/lib/libraylib.a"
        opengl32
        gdi32
        winmm
    )
else()
    target_link_libraries(
        pendulum PUBLIC
        raylib
        GL
        m
        pthread
        dl
        rt
        X11
    )
endif()
