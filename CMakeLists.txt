cmake_minimum_required(VERSION 3.14)

# Project name
project(apache-thrift-example LANGUAGES CXX)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)

# Apache Thrift local install tree
set(CMAKE_PREFIX_PATH "apache-thrift/build/install")

find_package(Thrift REQUIRED CONFIG)

message(STATUS "Thrift compiler found: ${THRIFT_COMPILER}")

# CMake configuring time Thrift compiler trigger
if(Thrift_FOUND)
    execute_process(COMMAND ${THRIFT_COMPILER} --gen cpp example.thrift
                    COMMAND ${THRIFT_COMPILER} --gen py example.thrift
                    COMMAND_ECHO STDOUT
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE THRIFT_COMPILER_RESULT)
    if(NOT THRIFT_COMPILER_RESULT EQUAL "0")
        message(FATAL_ERROR "${THRIFT_COMPILER} --gen cpp example.thrift")
    endif()
endif()

# CMake build time Thrift compiler trigger
#add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/include/Generated.hpp"
#                   COMMAND "${THRIFT_COMPILER}" --gen cpp "${CMAKE_CURRENT_SOURCE_DIR}/example.thrift")

#add_custom_target(generate_header ALL
#                  DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/include/Generated.hpp")

file(GLOB_RECURSE THRIFT_GEN_CODE ${CMAKE_CURRENT_SOURCE_DIR}/gen-cpp/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/gen-cpp/*.h)
# Filter out exemplary stub since it is overwritten all the time
list(FILTER THRIFT_GEN_CODE EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/gen-cpp/MultiplicationService_server.skeleton.cpp" )

add_executable(server)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/gen-cpp)
target_sources(server PRIVATE server.cpp ${THRIFT_GEN_CODE})
target_link_libraries(server PRIVATE thrift::thrift)