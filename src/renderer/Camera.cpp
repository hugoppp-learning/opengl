#include <iostream>
#include "Camera.hpp"

void Camera::Left() {
    m_position -= glm::cross(m_cameraFront, m_cameraUp) * m_speed;
}

void Camera::Forward() {
    m_position += m_speed * m_cameraFront;
}

void Camera::Right() {
    m_position += glm::cross(m_cameraFront, m_cameraUp) * m_speed;
}

void Camera::Back() {
    m_position -= m_speed * m_cameraFront;
}

void Camera::Up() {
    m_position += m_cameraUp * m_speed;
}

void Camera::Down() {
    m_position -= m_cameraUp * m_speed;
}

void Camera::Rotate(double xoffset, double yoffset) {
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;
    m_yaw += xoffset;
    m_pitch += yoffset;

    if(m_pitch > 89.0f)
        m_pitch = 89.0f;
    if(m_pitch < -89.0f)
        m_pitch = -89.0f;

    m_cameraFront.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_cameraFront.y = sin(glm::radians(m_pitch));
    m_cameraFront.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_cameraFront = glm::normalize(m_cameraFront);
    // also re-calculate the Right and Up vector
    m_cameraRight = glm::normalize(glm::cross(m_cameraFront, WORLD_UP));
    m_cameraUp    = glm::normalize(glm::cross(m_cameraRight, m_cameraFront));

    m_direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_direction.y = sin(glm::radians(m_pitch));
    m_direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_cameraFront = glm::normalize(m_direction);
}

Camera::Camera(float mMouseSensitivity) : m_mouseSensitivity(mMouseSensitivity) {}


