#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GEngine/Engine.hpp"
#include "GEngine/Shader.hpp"
#include "utils/Vertex.h"
#include "utils/Position.h"
#include "utils/Color.h"
#include "BG.hpp"

#include <iostream>
#include <vector>

class Player : public BG {
    private:
        std::vector<unsigned int> IDs={};                   //Esto me permite saber que IDs tienen cada forma que vaya a renderizar
        std::vector<unsigned int> argspace={3,3,3,3};       //Pos//Color//toPos//Color2
        std::vector<unsigned int> indexes={0,1,3,1,2,3};    //Indices de generacion
        //std::vector<float> vertexs={};                      //Vertices brutos del objeto
        std::vector<WVertex3D> vertexs={};                  //Vertices brutos del objeto

        std::vector<RGBColor> vertexcolors={};              //Gama de colores POR VERTICE

        std::vector<Coor3D> vcoors={                        //Coordenadas 3D POR VERTICE
            {-0.01f, -0.01f, 0.0f},
            {0.0f, 0.01f, 0.0f},
            {0.01f, -0.01f, 0.0f},
            {0.0f, -0.005f, 0.0f}
        };
        //General
        float sensibility = 100.0f;
        float radiusPos = 0.6f;
        float scale = 1.0f;
        float rotation = 0.0f;
        //Color
        RGBColor pcolor;
        //Transformaciones
        glm::mat4 model = glm::mat4(1.0f);
        //Objetos de referencia
        Engine* engine;
        Shader* ShaderPlayer;
        //Metodos de creacion
        void initShaders(){
            //ShaderPlayer = ShaderBG;
            //std::cout << "ShaderPlayer ptr: " << ShaderPlayer << std::endl;
            //engine->registerShader(ShaderPlayer);
        }
        void addColor( unsigned int vnum, RGBColor color){
            //std::cout << "Numero de vertices: " << vnum << std::endl;
            vertexcolors.clear();           //Limpio primero que nada
            for(int i=0; i<vnum; i++){
                //std::cout << "Insertando en index: " << (3 + i* offset) << std::endl;
                pushColor(vertexcolors, color);
            }
        }
        void rotatePlayerPos(float step){
            rotation+=step;
            //Transformacion
            model = glm::mat4(1.0f);    //Reiniciar la transformacion
            model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0,0.0,1.0));
            model = glm::translate(model, glm::vec3(radiusPos,0.0,0.0));
            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0,0.0,1.0));
            model = glm::scale(model, glm::vec3(scale));
        }
    public:
        Player()=default;
        Player(Engine* engine, Shader* shader, float sensibility, float size, float radiusPos, float rotation, RGBColor playerColor):
            engine(engine),
            ShaderPlayer(shader)
        {
            std::cout<<"Oh me creooo, dice Player"<<std::endl;
            initShaders();
            this->sensibility=sensibility;
            this->scale=size;
            this->rotation=rotation;
            this->radiusPos=radiusPos;
            pcolor=playerColor;
            //vertices
            addColor(vcoors.size(), playerColor);
            vertexs=setupMesh(vcoors, vertexcolors, vcoors, vertexcolors);
            //Memoria del objeto
            IDs.push_back(engine->createBuffer(vertexs,&indexes,12,argspace));
            //Transformar
            model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0,0.0,1.0));
            model = glm::translate(model, glm::vec3(radiusPos,0.0,0.0));
            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0,0.0,1.0));
            model = glm::scale(model, glm::vec3(size));
        }
        //Getters
        unsigned int getID(unsigned int index) const {
            return IDs.at(index);
        }
        const std::vector<WVertex3D>&getVertexs() const {
            return vertexs;
        }
        const std::vector<unsigned int>&getIndexes() const {
            return indexes;
        }
        const RGBColor&getColor() const {
            return pcolor;
        }
        /*
            Renderizar/Mostrar
        */
        void show() {
            ShaderPlayer->setMat4("Model", model);
            engine->renderPolygon(ShaderPlayer, this->getID(0), indexes.size());
        }
        /*
            Mover
        */
        void move(float step) {
            rotatePlayerPos(step);
        }
};

#endif