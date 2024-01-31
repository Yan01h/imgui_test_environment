# ImGuiTestEnvironment ImGui.cmake

# Copyright (c) 2024 Yan01h
# MIT license

######################
#    Thirdparties    #
######################

set(FREETYPE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparties/freetype)
if(NOT EXISTS "${FREETYPE_DIR}/CMakeLists.txt")
	message(FATAL_ERROR "Freetype was not found! Did you update the submodules?")
endif()
add_subdirectory(${FREETYPE_DIR})

#################
#    Sources    #
#################

set(IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparties/imgui)
set(IMGUI_BACKEND_DIR ${IMGUI_INCLUDE_DIR}/backends)

set(IMGUI_SOURCES
	${IMGUI_INCLUDE_DIR}/imconfig.h
	${IMGUI_INCLUDE_DIR}/imgui.h
	${IMGUI_INCLUDE_DIR}/imgui.cpp
	${IMGUI_INCLUDE_DIR}/imgui_demo.cpp
	${IMGUI_INCLUDE_DIR}/imgui_draw.cpp
	${IMGUI_INCLUDE_DIR}/imgui_internal.h
	${IMGUI_INCLUDE_DIR}/imgui_tables.cpp
	${IMGUI_INCLUDE_DIR}/imgui_widgets.cpp
	${IMGUI_INCLUDE_DIR}/imstb_rectpack.h
	${IMGUI_INCLUDE_DIR}/imstb_textedit.h
	${IMGUI_INCLUDE_DIR}/imstb_truetype.h
	${IMGUI_INCLUDE_DIR}/backends/imgui_impl_dx9.h
	${IMGUI_INCLUDE_DIR}/backends/imgui_impl_dx9.cpp
	${IMGUI_INCLUDE_DIR}/backends/imgui_impl_win32.h
	${IMGUI_INCLUDE_DIR}/backends/imgui_impl_win32.cpp
	${IMGUI_INCLUDE_DIR}/misc/freetype/imgui_freetype.h
	${IMGUI_INCLUDE_DIR}/misc/freetype/imgui_freetype.cpp
)

#################
#    Library    #
#################

add_library(imgui STATIC ${IMGUI_SOURCES})

target_link_libraries(imgui freetype)
target_include_directories(imgui PRIVATE ${IMGUI_INCLUDE_DIR})
target_include_directories(imgui PRIVATE ${FREETYPE_DIR}/include)

option(USE_FREETYPE "Build ImGui with freetype font rendering" ON)
if(USE_FREETYPE)
    add_compile_definitions(IMGUI_ENABLE_FREETYPE)
endif()