#ifndef BUFFER_INTERFACE_HPP
#define BUFFER_INTERFACE_HPP

#include <vector>

template <typename VertexType>
class Buffer {
    public:
        Buffer() = default;
        virtual ~Buffer() = default;
        virtual bool bind() = 0;
        virtual void updateSoftly(const std::vector<VertexType>& verts, const std::vector<unsigned int>* indexes = nullptr) = 0;
        virtual void updateHardly(const std::vector<VertexType>& verts, const std::vector<unsigned int>* indexes = nullptr) = 0;
        virtual void free() = 0;
};

#endif