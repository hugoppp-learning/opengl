
#ifndef OPENGLTEST_CAMERA_H
#define OPENGLTEST_CAMERA_H


#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

class Camera {
private:
    const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_cameraRight = glm::normalize(glm::cross(m_cameraFront, WORLD_UP));
    glm::vec3 m_position = glm::vec3(.0f, .0f, .0f);
    glm::vec3 m_direction = glm::vec3(.0f, .0f, .0f);
    double m_yaw = .0f;
    double m_pitch = .0f;
    float m_speed = .1f;
    float m_mouseSensitivity;
public:
    Camera(float mMouseSensitivity);

    glm::mat4 GetViewMatrix() {
        return glm::lookAt(m_position, m_position + m_cameraFront, m_cameraUp);
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
