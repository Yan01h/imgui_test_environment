// main.cpp

#include "imgui_test_environment.h"

#include <cstdio>

#include <d3d9.h>
#include <windows.h>

#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>

LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static bool g_Running = true;
static int g_NewWidth = 0;
static int g_NewHeight = 0;

int main()
{
    WNDCLASSEXA wndCls = {};
    wndCls.cbSize = sizeof(WNDCLASSEXA);
    wndCls.style = CS_CLASSDC;
    wndCls.hInstance = GetModuleHandleA(nullptr);
    wndCls.lpfnWndProc = WndProc;
    wndCls.lpszClassName = "imgui_test_environment";
    RegisterClassExA(&wndCls);

    HWND hwnd = CreateWindowA("imgui_test_environment", "ImGuiTestEnvironment", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, wndCls.hInstance, NULL);
    
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    LPDIRECT3D9 d3d9 = nullptr;
    LPDIRECT3DDEVICE9 d3dDevice = nullptr;
    D3DPRESENT_PARAMETERS d3dPP = {};

    d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

    d3dPP.AutoDepthStencilFormat = D3DFMT_D16;
    d3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dPP.EnableAutoDepthStencil = true;
    d3dPP.hDeviceWindow = hwnd;
    d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dPP.Windowed = true;

    d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

    d3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
    d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    d3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    setupImGui();

    ImGui_ImplDX9_Init(d3dDevice);
    ImGui_ImplWin32_Init(hwnd);

    D3DCOLOR clearColor = D3DCOLOR_RGBA(17, 33, 43, 255);

    while (g_Running)
    {
        static MSG msg;
        while (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (g_NewWidth != 0 && g_NewHeight != 0)
        {
            d3dPP.BackBufferWidth = g_NewWidth;
            d3dPP.BackBufferHeight = g_NewHeight;
            g_NewWidth = 0;
            g_NewHeight = 0;
            ImGui_ImplDX9_InvalidateDeviceObjects();
            d3dDevice->Reset(&d3dPP);
            ImGui_ImplDX9_CreateDeviceObjects();
        }

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        renderImGui();

        ImGui::EndFrame();

        d3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clearColor, 1.0f, 0);
        d3dDevice->BeginScene();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
        d3dDevice->EndScene();

        HRESULT hr = d3dDevice->Present(nullptr, nullptr, NULL, nullptr);
        if (hr == D3DERR_DEVICELOST && d3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
        {
            ImGui_ImplDX9_InvalidateDeviceObjects();
            d3dDevice->Reset(&d3dPP);
            ImGui_ImplDX9_CreateDeviceObjects();
        }

        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable && g_Running == true)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }        
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    d3dDevice->Release();
    d3d9->Release();

    DestroyWindow(hwnd);
    UnregisterClassA(wndCls.lpszClassName, wndCls.hInstance);

    return 0;
}

LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_NewWidth = (int)LOWORD(lParam);
        g_NewHeight = (int)HIWORD(lParam);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        g_Running = false;
        return 0;
    }

    return DefWindowProcA(hwnd, msg, wParam, lParam);
}