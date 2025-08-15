#ifndef MESH_INTERFACE_HPP
#define MESH_INTERFACE_HPP

class ContextManager;

//Abstract Factory of Buffers
class IBufferManager {
    protected:
        ContextManager* contextManager;
    public:
        IBufferManager() = default;
        void setContextManager(ContextManager* ctxManager){
            contextManager = ctxManager;
        }
        virtual ~IBufferManager(){}
        virtual Buffer<WVertex3D>* createBuffer(std::vector<WVertex3D>& verts, const std::vector<unsigned int>* indexes = nullptr) = 0;
};

class IMesh {
    public:
        IMesh(){}
        virtual ~IMesh(){}
        virtual bool bind() = 0;
        virtual bool noIndexes() = 0;
        virtual const size_t getIndexCount() const = 0;
        virtual const size_t getVertCount() const = 0;

};

template<typename VertexType>
class Mesh : public IMesh {
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
        bool noIndexes() override {
            return indexes.empty();
        }
        const size_t getIndexCount() const override {
            return indexes.size();
        }
        const size_t getVertCount() const override {
            return verts.size();
        }
        //Less relevant
        const std::vector<unsigned int>& getIndexes() const {
            return indexes;
        }
        const std::vector<VertexType>& getVerts() const {
            return verts;
        }
        bool bind() override {
            return buffer->bind();
        }
};

#endif