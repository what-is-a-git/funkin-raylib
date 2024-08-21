cmake_minimum_required(VERSION 3.12)

project(lua)

file(GLOB SRC ${PROJECT_SOURCE_DIR}/*.c)
add_library(${PROJECT_NAME} ${SRC})