#ifndef BUFFER_MANAGER_GL33_HPP
#define BUFFER_MANAGER_GL33_HPP

#include "../../include/GCore.hpp"
#include "Buffer33.hpp"

class BufferManagerGL33 : public IBufferManager {       
    public:
        BufferManagerGL33() = default;
        ~BufferManagerGL33() = default;
        Buffer<WVertex3D>* createBuffer(std::vector<WVertex3D>& verts, const std::vector<unsigned int>* indexes = nullptr) override {
            return new Buffer33<WVertex3D>(contextManager, verts, indexes);
        }
};

#endif