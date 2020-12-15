#include "Camera.h"

void Camera::Left() {
    position -= glm::cross(cameraFront, cameraUp) * speed;
}

void Camera::Forward() {
    position += speed * cameraFront;
}

void Camera::Right() {
    position += glm::cross(cameraFront, cameraUp) * speed;
}

void Camera::Back() {
    position -= speed * cameraFront;
}

void Camera::Up() {
    position += cameraUp * speed;
}

void Camera::Down() {
    position -= cameraUp * speed;
}

void Camera::Rotate(double xoffset, double yoffset) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;
    yaw += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    cameraFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront.y = sin(glm::radians(pitch));
    cameraFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(cameraFront);
    // also re-calculate the Right and Up vector
    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp    = glm::normalize(glm::cross(cameraRight, cameraFront));

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}


