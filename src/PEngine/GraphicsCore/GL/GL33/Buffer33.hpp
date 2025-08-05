#pragma once
#ifndef BUFFER_GL33_HPP
#define BUFFER_GL33_HPP

#include "../Buffer.hpp"
#include "../../../Utils/Vertex.h"

template<typename VertexType>
struct VertexDescriptor;

struct AttributeDescriptor {
    GLuint argsize;
    GLenum type;
    GLboolean normalized;
    size_t offset;
};

template<>
struct VertexDescriptor<WVertex3D> {
    static std::vector<AttributeDescriptor> getAttributes(){
        return {
            {3, GL_FLOAT, GL_FALSE, offsetof(WVertex3D, position)},
            {4, GL_FLOAT, GL_FALSE, offsetof(WVertex3D, color)}
        };
    }
};

template <typename VertexType>
class Buffer33 : public BufferGL<VertexType> {
    private:
        bool isFloatFamily(GLenum type){
            switch(type){
                case GL_FLOAT: return true;
                case GL_DOUBLE: return true;
                case GL_HALF_FLOAT: return true;
                default: return false;
            }
        }
    protected:
        unsigned int attribPointer = 0;
        unsigned int VAO = 0;
        unsigned int VBO = 0;
        unsigned int EBO = 0;
        void bindAttr(GLuint argsize, GLenum type, const void* ptr, GLboolean normalized){
            glEnableVertexAttribArray(attribPointer);
            if(!isFloatFamily(type)){
                glVertexAttribIPointer(attribPointer, argsize, type, sizeof(VertexType), ptr);
            }else{
                glVertexAttribPointer(attribPointer, argsize, type, normalized, sizeof(VertexType), ptr);
            }
            this->attribPointer++;
        }
        void make(std::vector<VertexType>& vertexs, const std::vector<unsigned int>* indexes){         
            //Vertex Array Object Creation
            glGenVertexArrays(1, &VAO);
            //Vertex Buffer Object Creation
            glGenBuffers(1, &VBO);
            //Element Buffer Object Creation
            if(indexes) glGenBuffers(1, &EBO);
            //Focus on VAO
            glBindVertexArray(VAO);
            //Focus on VBO
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertexs.size() * sizeof(VertexType), vertexs.data(), GL_STATIC_DRAW);
            //Focurs on EBO
            if(indexes){
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes->size() * sizeof(unsigned int), indexes->data(), GL_STATIC_DRAW);
            }
            //Unlink
            glBindVertexArray(0);
        }
        void map(){
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            const auto& attrs = VertexDescriptor<VertexType>::getAttributes();
            for (const auto& attr : attrs){
                bindAttr(attr.argsize, attr.type, (void*)attr.offset, attr.normalized);
            }
            glBindVertexArray(0);
        }
    public:
        Buffer33(std::vector<VertexType>& verts, const std::vector<unsigned int>* indexes){
            make(verts, indexes);
            map();
        };
        ~Buffer33() = default;
        const unsigned int getVAO_ID() const {
            return this->VAO;
        }
        const unsigned int getVBO_ID() const {
            return this->VBO;
        }
        const unsigned int getEBO_ID() const {
            return this->EBO;
        }
        void bind() override {
            glBindVertexArray(this->VAO);
        }
        void updateSoftly(const std::vector<VertexType>& verts, const std::vector<unsigned int>* indexes = nullptr) override {
            //Modify memory in VBO
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, verts.size()*sizeof(VertexType), verts.data());
            //Modify memory in EBO
            if(indexes){
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexes->size()*sizeof(unsigned int), indexes->data());
            }
        }
        void updateHardly(const std::vector<VertexType>& verts, const std::vector<unsigned int>* indexes = nullptr) override {
            //Modify all VBO
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(VertexType), verts.data(), GL_STATIC_DRAW);
            if(indexes){
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes->size()*sizeof(unsigned int), indexes->data(), GL_STATIC_DRAW);
            }
        }
        void free() override {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            if(EBO!=0) glDeleteBuffers(1, &EBO);
        }
};

#endif