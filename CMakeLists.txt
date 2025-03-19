cmake_minimum_required(VERSION 3.20)
project(PassGen C)

file(GLOB SOURCES "src/*.c")

include_directories("include/")

add_executable(passgen ${SOURCES})
