#pragma once

#include <glad/glad.h>
#include "VBO.h"

class VAO
{

public:
    // reference to vertex array object (VAO)
    GLuint id;

    // generates vertex array object 
    VAO();

    // links a VBO to the VAO using a certain layout
    void LinkAttrib(
        VBO &VBO,
        GLuint layout,
        GLuint numComponents,
        GLenum type,
        GLsizeiptr stride,
        void *offset);

    void Bind();
    void Unbind();
    void Delete();
};