//
// Created by hugop on 13.12.2020.
//

#ifndef OPENGLTEST_TEXTURE_H
#define OPENGLTEST_TEXTURE_H


class Texture {
public:
    std::string filePath;
    int width;
    int height;
    int nrChannels;
    unsigned int renderer_id;


    Texture(std::string filePath);
    ~Texture();

    void Unbind();

    void Bind(unsigned int slot = 0);
};


#endif //OPENGLTEST_TEXTURE_H
