#ifdef APIENTRY

#undef APIENTRY

#endif

#include <glad/glad.h> // glfw3.dll
#include <iostream>
#include <Windows.h>
#include "src/imgui.h"
#include "src/imgui_impl_glfw.h"
#include "src/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <Psapi.h>

#pragma comment (lib, "opengl32.lib")

int main() {
    glfwInit();

    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER | GLFW_DECORATED | GLFW_MAXIMIZED, 
                   GLFW_TRUE                    | GLFW_FALSE     | GLFW_TRUE);

    // Option = True\false

    GLFWwindow* window = glfwCreateWindow(1, 1, "PROGRAMM", NULL, NULL);
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core"); //3.3 OpenGL

    ImGuiIO& IO = ImGui::GetIO();
    IO.ConfigFlags = ImGuiConfigFlags_ViewportsEnable;
    IO.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\ebrimabd.ttf", 12.5f);
    IO.ConfigDpiScaleFonts = true;

    char path_DLL[260] = "\0";
    static int PID = 0;
    int display_w, display_h;
    
    while (!glfwWindowShouldClose(window)) {
        
        glfwWaitEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        ImGui::Begin("Extremy Injector");


        ImGui::TextColored(ImVec4(1, 0, 0.1, 1), "Thank you for using Extremy Injector");

        ImGui::SeparatorText("Options");

        if (ImGui::InputText("<- Enter Path to DLL", path_DLL, std::size(path_DLL))) {};
        if (ImGui::InputInt("<- Enter Process ID here!", &PID)) {};
        

        ImGui::Text("PID of the proccess: %d", PID);
        
        if (ImGui::Button("Inject!")) {
            if(PID != 0){
                HANDLE hmodule = OpenProcess(PROCESS_ALL_ACCESS, 0, PID);
                LPVOID LPvd = VirtualAllocEx(hmodule, nullptr, 260, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
                if (LPvd != 0) {
                    WriteProcessMemory(hmodule, LPvd, path_DLL, 260, nullptr);
                    CreateRemoteThread(hmodule, nullptr, 260, LPTHREAD_START_ROUTINE(LoadLibraryA), LPvd, 0, nullptr);
                    MessageBox(NULL, L"Injected succesfully!", L"Good!", MB_OK);
                }
                else {
                    MessageBox(NULL, L"Inject Error!!", L"Error", MB_ICONERROR | MB_OK);
                }
            }
            else if (path_DLL[0] == '\0') {
                MessageBox(NULL, L"Incorrect path to DLL!!", L"Error", MB_ICONERROR | MB_OK);
            }
            else {
                MessageBox(NULL, L"Incorrect PID!", L"Error", MB_ICONERROR | MB_OK);
            }
        }

        ImGui::SeparatorText("Exit");

        if (ImGui::Button("Exit")) {
            glfwSetWindowShouldClose(window, true);
        }


        ImGui::End();
        ImGui::Render();

        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (IO.ConfigFlags == ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }
    return 0;
}