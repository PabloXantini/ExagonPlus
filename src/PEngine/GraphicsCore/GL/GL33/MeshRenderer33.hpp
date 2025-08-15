#ifndef MESH_RENDERER_GL33_HPP
#define MESH_RENDERER_GL33_HPP

#include "../Renderer.hpp"
#include "../../include/Shader.hpp"

class MeshRenderer33 : public RendererGL {
    public:
        MeshRenderer33(IShader* shader): 
            RendererGL(shader)
        {}
        ~MeshRenderer33(){}
        void draw(IMesh* mesh) override {
            //Bind textures if it has
            //Bind and draw the Mesh
            if(!mesh->bind()) return;
            if(!mesh->noIndexes()){
                glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, 0);  
            }else {
                glDrawArrays(GL_TRIANGLES, 0, mesh->getVertCount());
            }
        }
};

#endif