#include <string>
#include "Texture.hpp"
#include <glad/glad.h>
#include <iostream>
#include <utility>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

Texture::Texture(std::string filePath)
    : m_filePath(std::move(filePath)), m_width(0), m_height(0), m_nrChannels(0), m_renderer_id(0){
    glGenTextures(1, &m_renderer_id);
    glBindTexture(GL_TEXTURE_2D, m_renderer_id);

    stbi_set_flip_vertically_on_load(1);
    unsigned char *data = stbi_load(this->m_filePath.c_str(), &m_width, &m_height, &m_nrChannels, 4);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        std::cout << "ERROR: Failed to load texture" << std::endl;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture(){
    glDeleteTextures(1, &m_renderer_id);
}

void Texture::Bind(unsigned int slot){
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_renderer_id);
}

void Texture::Unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}
