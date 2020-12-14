
#ifndef OPENGLTEST_WINDOWINITILIZER_H
#define OPENGLTEST_WINDOWINITILIZER_H


class WindowInitilizer {
public:
    static GLFWwindow *Init();

private:
    static void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length,
                                       const char *message,
                                       const void *userParam);

    static void printError(GLenum source, GLenum type, unsigned int id, GLenum severity, const char *message);
};


#endif //OPENGLTEST_WINDOWINITILIZER_H
