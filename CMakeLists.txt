cmake_minimum_required(VERSION 3.12)
project(pcl_toolkit)

set(CMAKE_CXX_STANDARD 17)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

find_package(pybind11 REQUIRED)

pybind11_add_module(pcl_toolkit reconstruct_range_image.cpp)
