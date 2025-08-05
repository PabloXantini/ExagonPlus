#ifndef RENDERER_OPENGL_INTERFACE_HPP
#define RENDERER_OPENGL_INTERFACE_HPP

#include <glad/glad.h>

#include "../include/GCore.hpp"

template<typename VertexType>
class RendererGL : public IRenderer<VertexType> {
    public:
        RendererGL(IShader* shader) : IRenderer<VertexType>(shader){}
        ~RendererGL(){}
};

#endif