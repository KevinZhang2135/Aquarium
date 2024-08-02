#include "VAO.h"

// generates vertex array object (VAO)
VAO::VAO()
{
    glGenVertexArrays(1, &id);
}

// links a VBO to the VAO using a certain layout
void VAO::LinkAttrib(
    VBO &VBO,
    GLuint layout,
    GLuint numComponents,
    GLenum type,
    GLsizeiptr stride,
    void *offset)
{
    VBO.Bind();

    // configure and enable the vertex attribute for OpenGL to parse the VBO
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);

    VBO.Unbind();
}

void VAO::Bind()
{
    glBindVertexArray(id);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &id);
}