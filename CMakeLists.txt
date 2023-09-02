# ImGuiTestEnvironment Root CMakeLists.txt

cmake_minimum_required(VERSION 3.7...3.27)

###############
#	Project   #
###############

project(ImGuiTestEnvironment LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(THIRDPARTIES_DIR ${CMAKE_SOURCE_DIR}/thirdparties)

add_subdirectory(src)

####################
#	Thirdparties   #
####################

add_subdirectory(${THIRDPARTIES_DIR}/imgui)