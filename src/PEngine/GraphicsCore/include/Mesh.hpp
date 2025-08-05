#ifndef MESH_INTERFACE_HPP
#define MESH_INTERFACE_HPP

//Abstract Factory of Buffers
class IBufferManager {
    public:
        IBufferManager() = default;
        virtual ~IBufferManager(){}
        virtual Buffer<WVertex3D>* createBuffer(std::vector<WVertex3D>& verts, const std::vector<unsigned int>* indexes = nullptr) = 0;
};

template<typename VertexType>
class Mesh {
    private:
        IBufferManager* bufferManager;
        Buffer<VertexType>* buffer;
        std::vector<VertexType> verts;
        std::vector<unsigned int> indexes;
        std::vector<short> textures;
    public:
        Mesh(IBufferManager* bufferMgr, std::vector<VertexType>& verts, const std::vector<unsigned int>* indexes = nullptr, const std::vector<short>* textures = nullptr):
            bufferManager(bufferMgr)
        {
            this->verts = verts;
            if(indexes) this->indexes = *indexes;
            if(textures) this->textures = *textures;
            buffer = bufferManager->createBuffer(verts, indexes);
        }
        const std::vector<unsigned int>& getIndexes() const {
            return indexes;
        }
        const std::vector<VertexType>& getVerts() const {
            return verts;
        }
        const size_t getIndexCount() const {
            return indexes.size();
        }
        const size_t getVertCount() const {\
            return verts.size();
        }
        virtual Buffer<VertexType>* getBuffer(){
            return buffer;
        }
};

#endif