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
#include "Renderer/GLDebugCallBack.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    GLFWwindow *window = glfwCreateWindow(
        800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        // initialize debug output
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
    glViewport(0, 0, 800, 600);

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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    Shader shader = Shader("../res/1.vert", "../res/1.frag");
    shader.Bind();
    VertexBuffer vb(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push(GL_FLOAT, 3);
    layout.Push(GL_FLOAT, 3);
    layout.Push(GL_FLOAT, 2);
    VertexArray va;
    va.AddBuffer(vb, layout);
    IndexBuffer ib(indices, 6);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();


//    Texture texture("../res/1.jpg");
    Texture texture("../res/holo.png");

//    shader.SetUniform("ourTexture", 0);
    Renderer renderer;
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(.2f, .2f, .2f, .2f);
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.Draw(va, ib, shader);
//        auto timeValue = (float) glfwGetTime();
//        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
//        shader.SetUniform("myColor", .0f, greenValue, .9f, .1f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}


