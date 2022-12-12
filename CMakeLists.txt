cmake_minimum_required(VERSION 3.5)

project(RK_KMP_StringSearcher LANGUAGES CXX)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

include_directories("include/")

FILE(GLOB SRCS
        "*.cpp"
	"src/*.cpp"
)

add_executable(${PROJECT_NAME} "src/main.cpp" ${SRCS})