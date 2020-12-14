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
#include "Renderer/WindowInitilizer.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);


int main() {

    GLFWwindow *window = WindowInitilizer::Init();

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
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        shader.Bind();
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, (float) glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        shader.SetUniformMatrix4v("transform", glm::value_ptr(trans));
        shader.Unbind();

        renderer.Draw(va, ib, shader);
        glfwSwapBuffers(window);
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
}
