#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "../utils/Vertex.h"

#include <iostream>
#include <vector>

class Buffer {
    private:
        unsigned int attribpointer=0;
        unsigned int argsused=0;
        unsigned int argssize;
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO=0;
    public:
        Buffer(const std::vector<WVertex3D>& verts, const std::vector<unsigned int>* indexes, int argssize){
            this->argssize=argssize;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            //Opcional
            if(indexes) glGenBuffers(1, &EBO);
            //Asignacion de memoria para VAO
            glBindVertexArray(VAO);
            //Asignacion de memoria para VBO
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(WVertex3D), verts.data(), GL_STATIC_DRAW);
            //Opcional: Asignacion de memoria para EBO
            if(indexes){
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes->size() * sizeof(unsigned int), indexes->data(), GL_STATIC_DRAW);
            }
            //Desvincular
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
        void addAttribute(unsigned int args){
            unsigned int argtest=argsused;
            if((argtest+args)>argssize) {
                std::cout<<"El numero de argumentos del buffer se ha excedido"<<std::endl;
                return;
            }
            //Vincula a memoria
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            //Establece el atributo
            glVertexAttribPointer(attribpointer, args, GL_FLOAT, GL_FALSE, argssize * sizeof(float), (void*)(argsused*sizeof(float)));
            glEnableVertexAttribArray(attribpointer);
            //Desvincular
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            //Incrementa el stride y el apuntador para mas atributos
            argsused+=args;
            attribpointer++;
        }
        //Actualizacion sin cambiar tamanio
        void update(const std::vector<WVertex3D>& verts, const std::vector<unsigned int>* indexes){
            //Asignacion de memoria para VBO
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, verts.size()*sizeof(WVertex3D), verts.data());
            //Opcional: Asignacion de memoria para EBO
            if(indexes){
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexes->size()*sizeof(unsigned int), indexes->data());
            }
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        //Actualizacion forzosa
        void updateAll(const std::vector<WVertex3D>& verts, const std::vector<unsigned int>* indexes){
            //Asignacion de memoria para VBO
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(WVertex3D), verts.data(), GL_STATIC_DRAW);
            //Opcional: Asignacion de memoria para EBO
            if(indexes){
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes->size() * sizeof(unsigned int), indexes->data(), GL_STATIC_DRAW);
            }
            //Desvincular
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            //glBindVertexArray(0);
        }
        void free(){
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
        }
        const unsigned int getVAO() const {
            return VAO;
        }
        const unsigned int getVBO() const {
            return VBO;
        }
        const unsigned int getEBO() const {
            return EBO;
        }
        const unsigned int getArgSize() const {
            return argssize;
        }
};

#endif