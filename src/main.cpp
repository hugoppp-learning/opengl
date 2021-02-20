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
#include "Chunk.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

bool disable_mouse;


void processInput(GLFWwindow *window);

void drawTutorialCubes(Shader &shader, glm::vec4 modelColor, glm::vec4 ambientColor, glm::vec4 defuseColor);

Camera camera(.1f);
Window window;

glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                        800.0f / 600.0f,
                                        0.1f,
                                        100.0f);

struct LightValues {
    glm::vec4 clear_color;
    glm::vec4 modelColor;
    glm::vec4 ambientColor;
    glm::vec4 defuseColor;
    float shininess;
};

void DrawImGui(LightValues &lv);

LightValues lightValues = {
    .clear_color = glm::vec4(0.189f, 0.193f, 0.201f, 1.000f),
    .modelColor = glm::vec4(0.635f, 0.551f, 0.770f, 1.000f),
    .ambientColor = glm::vec4(0.039f, 0.040f, 0.495f, 1.000f),
    .defuseColor = glm::vec4(0.873f, 0.794f, 0.171f, 1.000f),
    .shininess = 32
};

int main() {

    glfwSetCursorPosCallback(window.GetGLFWwindow(), mouse_callback);
    glfwSetWindowSizeCallback(window.GetGLFWwindow(), framebuffer_size_callback);

    Chunk chunk;
    std::cout << (int) chunk.at(10,10,10);


//    glm::vec3 transl(0.45f, 0.55f, 0.60f);

    std::vector<glm::vec3> cubPos(chunk.volume);

    for (int x = 0; x < chunk.x_size; ++x)
    for (int y = 0; y < chunk.y_size; ++y)
    for (int z = 0; z < chunk.z_size; ++z) {
        cubPos.emplace_back(x,y,z);
    }

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

        shader.SetUniform4f("u_modelColor", lightValues.modelColor);
        shader.SetUniform4f("u_ambientColor", lightValues.ambientColor);
        shader.SetUniform4f("u_defuseColor", lightValues.defuseColor);
        shader.SetUniform3f("u_lightPos", 10.5f, 10.5f, 10.5f);
        shader.SetUniform1f("u_shininess", lightValues.shininess);

        for (auto & cubPo : cubPos) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubPo);
            shader.SetUniformMatrix4f("u_m", glm::value_ptr(model));
            cube.mesh.Draw(shader);
        }

        drawTutorialCubes(shader, lightValues.modelColor, lightValues.ambientColor, lightValues.defuseColor);

        int display_w, display_h;
        glfwGetFramebufferSize(window.GetGLFWwindow(), &display_w, &display_h);
        glClearColor(lightValues.clear_color.x, lightValues.clear_color.y, lightValues.clear_color.z,
                     lightValues.clear_color.w);

        DrawImGui(lightValues);
        glfwSwapBuffers(window.GetGLFWwindow());
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void drawTutorialCubes(Shader &shader, glm::vec4 modelColor, glm::vec4 ambientColor, glm::vec4 defuseColor) {
    shader.SetUniform4f("u_modelColor", modelColor);
    shader.SetUniform4f("u_ambientColor", ambientColor);
    shader.SetUniform4f("u_defuseColor", defuseColor);
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

void DrawImGui(LightValues &lv) {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Moin");
    ImGui::ColorEdit3("clear color", (float *) &lv.clear_color);
    ImGui::ColorEdit3("ambient color", (float *) &lv.ambientColor);
    ImGui::ColorEdit3("model color", (float *) &lv.modelColor);
    ImGui::ColorEdit3("defuse color", (float *) &lv.defuseColor);
    ImGui::SliderFloat("shininess",  &lv.shininess, 1, 300);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

