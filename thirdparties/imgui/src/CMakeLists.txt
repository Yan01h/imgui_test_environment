# ImGui Src CMakeLists.txt

###############
#	Sources   #
###############

set(IMGUI_SRC
	imconfig.h
	imgui.cpp
	imgui_demo.cpp
	imgui_draw.cpp
	imgui_impl_dx9.cpp
	imgui_impl_win32.cpp
	imgui_internal.h
	imgui_tables.cpp
	imgui_widgets.cpp
	imstb_rectpack.h
	imstb_textedit.h
	imstb_truetype.h
)

source_group(src FILES ${IMGUI_TEST_SRC})

add_library(ImGui STATIC ${IMGUI_SRC})

target_include_directories(ImGui PUBLIC ${THIRDPARTIES_DIR}/imgui/include/imgui)