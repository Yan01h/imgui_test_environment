# ImGuiTestEnvironment Src CMakeLists.txt

###############
#	Sources   #
###############

set(IMGUI_TEST_SRC
	imgui_test_environment.h
	imgui_test_environment.cpp
	main.cpp
)

source_group(src FILES ${IMGUI_TEST_SRC})

add_executable(ImGuiTestEnvironment ${IMGUI_TEST_SRC})

####################
#	Dependencies   #
####################

target_link_libraries(ImGuiTestEnvironment ImGui)
target_link_libraries(ImGuiTestEnvironment d3d9.lib)

target_include_directories(ImGuiTestEnvironment PUBLIC ${THIRDPARTIES_DIR}/imgui/include)