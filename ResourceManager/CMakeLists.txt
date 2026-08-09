cmake_minimum_required(VERSION 3.15)

project(ResourceManagerProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Header-only interface library for the ResourceManager header
add_library(resourcemanager INTERFACE)
target_include_directories(resourcemanager INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(resourcemanager INTERFACE cxx_std_20)

# For MSVC ensure __cplusplus is correctly reported (helps libraries relying on it)
if(MSVC)
	target_compile_options(resourcemanager INTERFACE /Zc:__cplusplus)
endif()

# Optional example executable: only added if app/main.cpp exists
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/app/main.cpp")
	add_executable(example app/main.cpp)
	target_link_libraries(example PRIVATE resourcemanager)
endif()

message(STATUS "Configured ResourceManagerProject")
