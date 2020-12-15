
#ifndef OPENGLTEST_CAMERA_H
#define OPENGLTEST_CAMERA_H


#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

class Camera {
private:
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 position = glm::vec3(.0f, .0f, 4.0f);
    glm::vec3 direction;
    float speed = 1;
public:
    glm::mat4 GetViewMatrix() {
        return glm::lookAt(position, position + cameraFront, cameraUp);
    }

    void Left();

    void Right();

    void Back();

    void Forward();
};


#endif //OPENGLTEST_CAMERA_H
