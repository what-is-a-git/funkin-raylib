cmake_minimum_required(VERSION 3.12)

project(FunkinRaylib)

set(SRC
    src/main.c
    src/str.c
    src/lua_frontend.c
    src/lua_wrapper.c
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_subdirectory(src/vendor/raylib)
add_subdirectory(src/vendor/lua)

include_directories(include)
include_directories(include/vendor)
include_directories(src/vendor/lua)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} lua)

file(COPY assets/ DESTINATION bin/assets)