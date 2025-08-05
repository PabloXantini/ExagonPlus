#ifndef MESH_RENDERER_GL33_HPP
#define MESH_RENDERER_GL33_HPP

#include "../Renderer.hpp"
#include "../../include/Shader.hpp"

template<typename VertexType>
class MeshRenderer33 : public RendererGL<VertexType> {
    public:
        MeshRenderer33(IShader* shader): 
            RendererGL<VertexType>(shader)
        {}
        ~MeshRenderer33(){}
        void draw(Mesh<VertexType>* mesh) override {
            this->shader->use();
            mesh->getBuffer()->bind();
            if(!mesh->getIndexes().empty()){
                glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, 0);  
            }else {
                glDrawArrays(GL_TRIANGLES, 0, mesh->getVertCount());
            }
        }
};

#endif