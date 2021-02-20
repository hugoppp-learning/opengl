#pragma once

class Window {
public:
    GLFWwindow *GetGLFWwindow() {
        return glfwWindow;
    }

    Window();

private:
    GLFWwindow *glfwWindow = nullptr;

    static void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length,
                                       const char *message,
                                       const void *userParam);

    static void printError(GLenum source, GLenum type, unsigned int id, GLenum severity, const char *message);

    void initImGui() const;

    static void initGL() ;

};
