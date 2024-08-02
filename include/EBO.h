#pragma once

#include <glad/glad.h>

class EBO {

    public:
        // reference to element buffer object (EBO)
        GLuint id;

        // generates element buffer object
        EBO(GLuint *indices, GLsizeiptr size);

        void Bind();
        void Unbind();
        void Delete(); 
}; 