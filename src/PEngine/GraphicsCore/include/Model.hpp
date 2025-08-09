#ifndef MODEL_HPP
#define MODEL_HPP

#include "Mesh.hpp"

#include <memory>
#include <vector>

class Model {
    private:
        std::vector<std::unique_ptr<IMesh>> meshes;
    public:
        Model(){}
        ~Model(){}
        std::vector<std::unique_ptr<IMesh>>& getMeshes() {
            return meshes;
        }
        void addMesh(std::unique_ptr<IMesh> mesh){
            meshes.push_back(std::move(mesh));
            //do texture remapping
        }
};

#endif