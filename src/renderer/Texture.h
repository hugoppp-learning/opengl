//
// Created by hugop on 13.12.2020.
//

#ifndef OPENGLTEST_TEXTURE_H
#define OPENGLTEST_TEXTURE_H


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


#endif //OPENGLTEST_TEXTURE_H
