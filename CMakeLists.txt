cmake_minimum_required(VERSION 3.14)
project(CPPParsersDemo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(extern/json)
add_subdirectory(extern/yaml-cpp)
add_subdirectory(extern/tinyxml2)
add_subdirectory(extern/tomlplusplus)
# inih 没有官方CMake，直接添加头文件和源文件
set(INIH_SOURCES
    extern/inih/ini.c
    extern/inih/cpp/INIReader.cpp
)
add_library(inih STATIC ${INIH_SOURCES})
target_include_directories(inih PUBLIC extern/inih extern/inih/cpp)

include_directories(
    include
    extern/json/single_include
    extern/yaml-cpp/include
    extern/tinyxml2
    extern/tomlplusplus/include
    extern/inih
    src
)

file(GLOB SRC
    src/*.cpp
)

add_executable(demo example/demo.cpp ${SRC})
target_link_libraries(demo
    nlohmann_json::nlohmann_json
    yaml-cpp
    tinyxml2
    inih
)