// imgui_test_environment.cpp

#include "imgui_test_environment.h"

#include <imgui.h>

const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 960;

void setupImGui()
{
    ImGuiIO& io = ImGui::GetIO();
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    ImGui::StyleColorsDark();
}

void renderImGui()
{
    // Your imgui code here
    ImGui::Begin("Test Window");

    ImGui::Text("Hello World!");
    ImGui::Button("Click");

    ImGui::End();
}