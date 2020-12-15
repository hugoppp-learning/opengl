
#ifndef OPENGLTEST_WINDOW_H
#define OPENGLTEST_WINDOW_H


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

    void initImgui();

    void initImGui() const;

    static void initGL() ;
};


#endif //OPENGLTEST_WINDOW_H
