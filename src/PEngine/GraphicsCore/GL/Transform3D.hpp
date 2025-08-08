#ifndef TRANSFORM_3D_GL_HPP
#define TRANSFORM_3D_GL_HPP

#include "../include/Transformation3D.hpp"
#include "sAdapter.h"

class Transform3D_GL : public Transform3D {
    private:
        glm::mat4 model = glm::mat4(1.0f);
    public:
        Transform3D_GL(){}
        ~Transform3D_GL(){}
        void rotate(float DegX = 0.0f, float DegY = 0.0f, float DegZ = 0.0f) override {
            if(DegX!=0.0f) this->model = glm::rotate(model, glm::radians(DegX), glm::vec3(1.0, 0.0, 0.0));
            if(DegY!=0.0f) this->model = glm::rotate(model, glm::radians(DegY), glm::vec3(0.0, 1.0, 0.0));
            if(DegZ!=0.0f) this->model = glm::rotate(model, glm::radians(DegZ), glm::vec3(0.0, 0.0, 1.0));
        }
        void translate(Vec3f objective) override {
            glm::vec3 vec(objective.X, objective.Y, objective.Z);
            this->model = glm::translate(model, vec);
        }
        void scale(float factor) override {
            this->model = glm::scale(model, glm::vec3(factor));
        }
        void scale_local(Vec3f factor) override {
            glm::vec3 vec(factor.X, factor.Y, factor.Z);
            this->model = glm::scale(model, vec);
        }
        void reset() override {
            this->model = glm::mat4(1.0f);
        }
        void apply(IShader* shader, const std::string &name) override {
            Mat4f mat = fromGLMMat4(model);
            shader->use();
            shader->setMat4(name, mat);      
        }
};

#endif