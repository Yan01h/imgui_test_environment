# ImGuiTestEnvironment Root CMakeLists.txt

cmake_minimum_required(VERSION 3.7...3.27)

###############
#	Project   #
###############

# Disable in-source builds
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Other settings
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(MSVC)
    add_compile_options(/MP)
endif()

option(GIT_SUBMODULE "Check submodules during build" ON)
if(GIT_SUBMODULE)
    find_package(Git QUIET)
    if(GIT_FOUND)
        message(STATUS "Updating submodules")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMODULE_RESULT
        )
        if(NOT GIT_SUBMODULE_RESULT EQUAL "0")
            message(SEND_ERROR "'git submodule update --init --recursive' failed! ${GIT_SUBMODULE_RESULT}")
        endif()
    else()
        message(WARNING "Git was not found! You need to update the submodules manually.")
    endif()
endif()

######################
#    Thirdparties    #
######################

# ImGui
include(ImGui)

#################
#    Project    #
#################

project(ImGuiTestEnvironment LANGUAGES CXX)

# Source files
set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui_test_environment.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui_test_environment.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

# Add library
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Include paths
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_BACKEND_DIR})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE d3d9.lib)