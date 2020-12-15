
//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_glfw.h"
//#include "imgui/imgui_impl_opengl3.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Renderer/Texture.h>

#include "Renderer/Shader.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexBufferLayout.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <renderer/Camera.h>
#include "Renderer/Window.h"
//#include <imgui/imgui.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void drawImGui(GLFWwindow *window);

void processInput(GLFWwindow *window);

bool show_demo_window = true;
bool show_another_window = false;

Camera camera;


int main() {

    Window window;

// Load Fonts
// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
// - Read 'docs/FONTS.md' for more instructions and details.
// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
//io.Fonts->AddFontDefault();
//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
//IM_ASSERT(font != NULL);

// Our state
    float vertices[] = {
        //    positions            colors             tex pos
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// LB
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// LT
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,// RT
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,// RB
    };

    unsigned int indices[] = {
        0, 1, 3,
        3, 2, 1,
    };

    Shader shader = Shader("../res/1.vert", "../res/1.frag");
    shader.Bind();
    VertexBuffer vb(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    VertexArray va;
    va.AddBuffer(vb, layout);
    IndexBuffer ib(indices, 6);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

//    Texture texture("../res/1.jpg");
    Texture texture("../res/holo.png");

    Renderer renderer;
    glm::mat4 projection =
        glm::perspective(glm::radians(45.0f),
                         800.0f / 600.0f,
                         0.1f,
                         100.0f);


    glm::vec3 transl (0.45f, 0.55f, 0.60f);
    glm::vec4 clear_color (0.45f, 0.55f, 0.60f, 1.00f);
    // Main loop
    while (!glfwWindowShouldClose(window.GetGLFWwindow())) {
        processInput(window.GetGLFWwindow());
        renderer.Clear();
        shader.Bind();

        glm::mat4 view =
//            glm::translate(glm::mat4(1.0f),
//                          glm::vec3(0.0f, 0.0f, -4.0f));

            camera.GetViewMatrix();
//            var.length();

            glm::mat4 model =
                glm::translate(
                    glm::rotate(glm::mat4(1.0f),
                                glm::radians(-55.0f),
                                glm::vec3(1.0f, 0.0f, 0.0f)),
                                transl);

            auto mvp = projection * view/* * model*/;
            shader.SetUniformMatrix4v("mvp", glm::value_ptr(mvp));
            renderer.Draw(va, ib, shader);
        shader.Unbind();

        {
            glfwPollEvents();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello OpenGL");
            ImGui::Text("This is some useful text.");
            ImGui::ColorEdit3("clear color", (float*)&clear_color);
//            ImGui::SliderFloat3("translation", (float*)&transl, -10, 10, "%.2f",0);

            if (ImGui::Button("Button"))
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window.GetGLFWwindow(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window.GetGLFWwindow());
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.Forward();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.Back();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.Left();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.Right();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glm::mat4 projection =
        glm::perspective(glm::radians(45.0f),
                         (float)width / (float)height,
                         0.1f,
                         100.0f);
}

