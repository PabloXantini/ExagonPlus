#ifndef RENDERER_OPENGL_INTERFACE_HPP
#define RENDERER_OPENGL_INTERFACE_HPP

#include <glad/glad.h>

#include "../include/GCore.hpp"

class RendererGL : public Renderer {
    public:
        RendererGL(IShader* shader) : Renderer(shader){}
        ~RendererGL(){}
};

#endif