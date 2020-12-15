
#include "Camera.h"

void Camera::Left() {
    position -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
}

void Camera::Forward() {
    position += speed * cameraFront;
}

void Camera::Right() {
    position += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
}

void Camera::Back() {
    position -= speed * cameraFront;
}
