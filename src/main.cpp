#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <renderer/Texture.h>

#include "renderer/Shader.h"
#include "renderer/Buffer.h"
#include "renderer/VertexBufferLayout.h"
#include "renderer/VertexArray.h"
#include "renderer/Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <renderer/Camera.h>
#include <renderer/Mesh.h>
#include "renderer/Window.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void drawImGui(GLFWwindow *window);

#pragma clang diagnostic pop

void processInput(GLFWwindow *window);

Camera camera(.1f);

int main() {

    Window window;
    float vertices_holo[] = {
        //    positions            colors             tex pos
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// LB
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// LT
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,// RT
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,// RB
    };


//    std::vector<Vertex>(Vertex(-0.5f, -0.5f, 0.0f, <#initializer#>));
//    Mesh holo_mesh();

    float vertices_cubes[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        3, 2, 1,
    };

    glfwSetCursorPosCallback(window.GetGLFWwindow(), mouse_callback);

    Shader shader = Shader("../res/1.vert", "../res/1.frag");
//    shader.Bind();
//    VertexBuffer vb_holo(vertices_holo, sizeof(vertices_holo));
//    VertexBufferLayout layout;
//    layout.Push<float>(3);
//    layout.Push<float>(3);
//    layout.Push<float>(2);
//    VertexArray va_holo;
//    va_holo.AddBuffer(vb_holo, layout);
//    IndexBuffer ib_holo(indices, 6);
//    Texture texture_holo("../res/holo.png");

//    Mesh holo (holo);


    VertexBuffer vb_cubes(vertices_cubes, sizeof(vertices_cubes));
    VertexBufferLayout layout_cubes;
    layout_cubes.Push<float>(3);
    layout_cubes.Push<float>(2);
    VertexArray vao_Cube;
    vao_Cube.AddBuffer(vb_cubes, layout_cubes);


    Renderer renderer;
    glm::mat4 projection =
        glm::perspective(glm::radians(45.0f),
                         800.0f / 600.0f,
                         0.1f,
                         100.0f);

    glm::vec3 transl(0.45f, 0.55f, 0.60f);
    glm::vec4 clear_color(0.45f, 0.55f, 0.60f, 1.00f);

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
//    VertexArray::Unbind();
//    VertexBuffer::Unbind();
//    IndexBuffer::Unbind();
//    Shader::Unbind();
    shader.Bind();
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window.GetGLFWwindow())) {
        processInput(window.GetGLFWwindow());
        Renderer::Clear();

        glm::mat4 view = camera.GetViewMatrix();

        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            auto mvp = projection * view * model;
            shader.SetUniformMatrix4v("u_mvp", glm::value_ptr(mvp));
            Renderer::DrawArrays(vao_Cube, shader, 36);

        }

        auto mvp = projection * view; // * model;
        shader.SetUniformMatrix4v("u_mvp", glm::value_ptr(mvp));
//        Renderer::Draw(va_holo, ib_holo, shader);

        {
            glfwPollEvents();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello OpenGL");
            ImGui::Text("This is some useful text.");
            ImGui::ColorEdit3("clear color", (float *) &clear_color);
//            ImGui::SliderFloat3("translation", (float*)&transl, -10, 10, "%.2f",0);

            if (ImGui::Button("Button"))
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            ImGui::End();
        }

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window.GetGLFWwindow(), &display_w, &display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window.GetGLFWwindow());
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    static double lastX = .0f;
    static double lastY = .0f;
    static bool firstMouse = true;
    static double pitch = .0;
    static double yaw = -90.0;
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;


    pitch += xoffset;
    yaw += yoffset;
    camera.Rotate(xoffset, yoffset);
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
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.Up();
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        camera.Down();
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glm::mat4 projection =
        glm::perspective(glm::radians(45.0f),
                         (float) width / (float) height,
                         0.1f,
                         100.0f);
}

#pragma clang diagnostic pop
