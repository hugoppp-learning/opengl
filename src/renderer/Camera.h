
#ifndef OPENGLTEST_CAMERA_H
#define OPENGLTEST_CAMERA_H


#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

class Camera {
private:
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
//    const glm::vec3 RIGHT = ;

    glm::vec3 position = glm::vec3(.0f, .0f, .0f);
    glm::vec3 direction = glm::vec3(.0f, .0f, .0f);
    double yaw = .0f;
    double pitch = .0f;
    float speed = .1f;
    float MouseSensitivity = .1f;
public:
    glm::mat4 GetViewMatrix() {
        return glm::lookAt(position, position + cameraFront, cameraUp);
    }

    void Left();

    void Right();

    void Back();

    void Forward();

    void Down();

    void Up();

    void Rotate(double xoffset, double yoffset);

};


#endif //OPENGLTEST_CAMERA_H
