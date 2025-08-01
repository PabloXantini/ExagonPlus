#ifndef BUFFER_OPENGL_INTERFACE_HPP
#define BUFFER_OPENGL_INTERFACE_HPP

#include <glad/glad.h>

#include "../include/Buffer.hpp"

class BufferGL : public Buffer {
    public:
        BufferGL() = default;
        ~BufferGL() = default;
};

#endif