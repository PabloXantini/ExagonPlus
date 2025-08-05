#ifndef BUFFER_OPENGL_INTERFACE_HPP
#define BUFFER_OPENGL_INTERFACE_HPP

#include <glad/glad.h>

#include "../include/Buffer.hpp"

template <typename VertexType>
class BufferGL : public Buffer<VertexType> {
    public:
        BufferGL() = default;
        ~BufferGL() = default;
};

#endif