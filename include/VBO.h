#pragma once

#include <glad/glad.h>

class VBO {
    public:
        // reference to vertex buffer object (VBO)
        GLuint id;

        // generates vertex buffer object 
        VBO(GLfloat *vertices, GLsizeiptr size);

        void Bind();
        void Unbind();
        void Delete(); 
}; 