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
#include <renderer/Mesh.hpp>
#include <renderer/Meshes/Cube.hpp>
#include "renderer/Window.hpp"
#include "ChunkManager.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

bool disable_mouse;


void processInput(GLFWwindow *window);

void drawTutorialCubes(Shader &shader);

Camera camera(.1f);
Window window;

glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                        1600.0f / 1200.0f,
                                        0.1f,
                                        100.0f);

struct LigtMaterial {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float quadratic;
    float linear;
};

struct Material {
    glm::vec3 clear;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

void DrawImGui(Material &m, LigtMaterial &l);


int main() {

    glfwSetCursorPosCallback(window.GetGLFWwindow(), mouse_callback);
    glfwSetWindowSizeCallback(window.GetGLFWwindow(), framebuffer_size_callback);

    Material material = {
        .clear = glm::vec3(0.189f, 0.193f, 0.201f),
        .ambient = glm::vec3(0.25, 0.20725, 0.20725),
        .diffuse = glm::vec3(1.f, 0.829, 0.829),
        .specular = glm::vec3(0.296648, 0.296648, 0.296648),
        .shininess = 2.8f
    };
    LigtMaterial light = {
        .ambient = glm::vec3(0.160f, 0.181f, 0.265f),
        .diffuse = glm::vec3(0.961f, 0.961f, 0.961f),
        .specular = glm::vec3(0.961f, 0.961f, 0.961f),
        .quadratic = 0.032f,
        .linear = 0.09f,
    };

    Cube cube;
    Shader shader = Shader("../res/colored.vert", "../res/colored.frag");
    shader.Bind();
    glEnable(GL_DEPTH_TEST);


    while (!glfwWindowShouldClose(window.GetGLFWwindow())) {
        processInput(window.GetGLFWwindow());
        Renderer::Clear();

        glm::mat4 view = camera.GetViewMatrix();
        shader.SetUniformMatrix4f("u_v", glm::value_ptr(view));
        shader.SetUniformMatrix4f("u_p", glm::value_ptr(projection));

        shader.SetUniform3f("u_cameraPos", camera.GetPosition());

        shader.SetUniform3f("u_material.ambient", material.ambient);
        shader.SetUniform3f("u_material.diffuse", material.diffuse);
        shader.SetUniform3f("u_material.specular", material.specular);
        shader.SetUniform1f("u_material.shininess", material.shininess);

        shader.SetUniform3f("u_light.ambient", light.ambient);
        shader.SetUniform3f("u_light.diffuse", light.diffuse);
        shader.SetUniform3f("u_light.specular", light.specular);
        shader.SetUniform1f("u_light.quadratic", light.quadratic);
        shader.SetUniform1f("u_light.linear", light.linear);
        shader.SetUniform3f("u_light.position", 10.5f, 10.5f, 10.5f);


        drawTutorialCubes(shader);

        int display_w, display_h;
        glfwGetFramebufferSize(window.GetGLFWwindow(), &display_w, &display_h);
        glClearColor(material.clear.x, material.clear.y, material.clear.z, 1);

        DrawImGui(material, light);
        glfwSwapBuffers(window.GetGLFWwindow());
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void drawTutorialCubes(Shader &shader) {
    Cube cube;
    glm::vec3 cubePositios[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };


    for (unsigned int i = 0; i < 10; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositios[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        shader.SetUniformMatrix4f("u_m", glm::value_ptr(model));
        cube.mesh.Draw(shader);
    }
}

void DrawImGui(Material &m, LigtMaterial &l) {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    {
        using namespace ImGui;
        NewFrame();
        Begin("Moin");

        static bool useAmbient = true;
        Checkbox("use ambient as clear color", &useAmbient);
        if (useAmbient) {
            m.clear = l.ambient;
        } else {
            ColorEdit3("##1111", (float *) &m.clear);
        }
        Text("Model");
        ColorEdit3("ambient color##1", (float *) &m.ambient);
        ColorEdit3("diffuse color##1", (float *) &m.diffuse);
        ColorEdit3("specular color##1", (float *) &m.specular);
        SliderFloat("shininess", &m.shininess, 1, 300);

        Separator();

        Text("Light");
        ColorEdit3("ambient color##2", (float *) &l.ambient);
        ColorEdit3("diffuse color##2", (float *) &l.diffuse);
        ColorEdit3("specular color##2", (float *) &l.specular);
        InputFloat("quadratic", (float *) &l.quadratic, 0.000007, 2);
        InputFloat("linear", (float *) &l.linear, 0.001f, 1.0f);
        Separator();

        Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / GetIO().Framerate,
             GetIO().Framerate);
        End();

        Render();
        ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
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

