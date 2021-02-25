#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <renderer/Texture.hpp>
#include "renderer/Shader.hpp"
#include "renderer/Buffer.hpp"
#include "renderer/VertexBufferLayout.hpp"
#include "renderer/VertexArray.h"
#include "renderer/Renderer.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <renderer/Camera.hpp>
#include "renderer/Window.hpp"
#include "ChunkManager.hpp"
#include "Chunk.hpp"
#include "ChunkMeshGenerator.hpp"

struct Material {
    glm::vec3 clear = glm::vec3(0.6, 0.6, 0.6);
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void DrawImGui(Material &m);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void processInput(GLFWwindow *window);

bool disable_mouse;
Camera camera(.1f);
Window window;
glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                        1600.0f / 1200.0f,
                                        0.1f,
                                        10000.0f);

int main() {

    glfwSetCursorPosCallback(window.GetGLFWwindow(), mouse_callback);
    glfwSetWindowSizeCallback(window.GetGLFWwindow(), framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    Shader shader = Shader("../res/block.vert", "../res/block.frag");
    shader.Bind();

    Material material;
    Chunk chunk;
    ChunkMesh mesh(chunk);
    VertexArray vao;
    VertexBuffer vbo(&mesh.GetData().front(), mesh.GetData().size() * sizeof(Triangle));
    vao.AddBuffer(vbo, VertexBufferLayout().Push<float>(3).Push<char>(3).Push<char>(1));
    vbo.Bind();

    while (!glfwWindowShouldClose(window.GetGLFWwindow())) {
        processInput(window.GetGLFWwindow());
        Renderer::Clear();

        Renderer::DrawArrays(vao, shader, mesh.GetData().size() * sizeof (Triangle));

        glm::mat4 view = camera.GetViewMatrix();
        shader.SetUniformMatrix4f("u_v", glm::value_ptr(view));
        shader.SetUniformMatrix4f("u_p", glm::value_ptr(projection));

        glClearColor(material.clear.x, material.clear.y, material.clear.z, 1);

        DrawImGui(material);
        glfwSwapBuffers(window.GetGLFWwindow());
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void DrawImGui(Material &m) {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    {
        ImGui::NewFrame();
        ImGui::Begin("Moin");

        ImGui::ColorEdit3("##1111", (float *) &m.clear);
        ImGui::Separator();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);

        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (disable_mouse)
        return;
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
    if (glfwGetKey(window, GLFW_KEY_3)) {
        disable_mouse = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    if (glfwGetKey(window, GLFW_KEY_4)) {
        disable_mouse = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

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

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glad_glViewport(0, 0, width, height);
    projection =
        glm::perspective(glm::radians(45.0f),
                         (float) width / (float) height,
                         0.1f,
                         100.0f);
}

