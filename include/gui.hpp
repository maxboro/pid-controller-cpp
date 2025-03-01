#ifndef GUI_HPP
#define GUI_HPP

// gui
#include "imgui.h"
#include "implot.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <atomic>
#include <vector>

int render(
        std::shared_ptr<std::vector<double>> alt_log_ptr, 
        std::shared_ptr<std::vector<double>> t_log_ptr,
        std::shared_ptr<std::mutex> mutex_ptr,
        std::atomic<bool>* stop_flag_ptr
    ) {

    if (!glfwInit()) return -1;
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui + ImPlot", NULL, NULL);
    if (!window) return -1;
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    ImGui::CreateContext();
    ImPlot::CreateContext();
    
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    while (!glfwWindowShouldClose(window) && !stop_flag_ptr->load()) {
        glfwPollEvents();

        std::vector<double> alt_copy, t_copy;
        {
            std::lock_guard<std::mutex> lock(*mutex_ptr);
            alt_copy = *alt_log_ptr;
            t_copy = *t_log_ptr;
        }

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Start ImGui frame
        ImGui::Begin("Simulation Plot");
        if (ImPlot::BeginPlot("Altitude dynamics")) {
            int count = static_cast<int>(t_copy.size());
            ImPlot::PlotLine("Altitude", t_copy.data(), alt_copy.data(), count);
            ImPlot::EndPlot();
        }
        ImGui::End();

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

#endif
