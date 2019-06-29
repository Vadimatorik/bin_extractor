CMAKE_MINIMUM_REQUIRED(VERSION 3.10.2)

project(bin_extractor CXX ASM)
SET(CMAKE_CXX_STANDARD 14)

include_directories(
        "bin_extractor/inc"
        "cmd_controller/inc"
)

file(GLOB SOURCES
        "*.cpp"
        "*/src/*.cpp")

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND size --format=berkeley ${PROJECT_NAME})