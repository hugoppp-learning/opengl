#pragma once
#include <string>

class Texture {
public:
    std::string m_filePath;
    int m_width;
    int m_height;
    int m_nrChannels;
    unsigned int m_renderer_id;


    Texture(std::string filePath);
    ~Texture();

    void Unbind();

    void Bind(unsigned int slot = 0);
};
