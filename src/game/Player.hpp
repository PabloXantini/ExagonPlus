#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GEngine/Engine.hpp"
#include "GEngine/Shader.hpp"
#include "utils/Position.h"
#include "utils/Color.h"
#include "BG.hpp"

#include <iostream>
#include <vector>

class Player : public BG {
    private:
        std::vector<unsigned int> IDs={};                   //Esto me permite saber que IDs tienen cada forma que vaya a renderizar
        std::vector<unsigned int> argspace={3,3,3};           //Pos//Color//toPos
        unsigned int argsused=0;
        unsigned int argpointer=0;
        std::vector<unsigned int> indexes={0,1,3,1,2,3};    //Indices de generacion
        std::vector<float> vertexs={};                      //Vertices brutos del objeto

        std::vector<RGBColor> vertexcolors={};              //Gama de colores POR VERTICE

        std::vector<Coor3D> vcoors={                        //Coordenadas 3D POR VERTICE
            {-0.01f, -0.01f, 0.0f},
            {0.0f, 0.01f, 0.0f},
            {0.01f, -0.01f, 0.0f},
            {0.0f, -0.005f, 0.0f}
        };
        //General
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
        /*
            Reserva el siguiente espacio de atributos, como recomendacion se llama al final de cada insercion de valores
        */
        void reserveArgSpace(){
            argsused+=argspace.at(argpointer);
            argpointer++;
        }
        unsigned int calculateStride(){
            unsigned int argstride=0;
            for(int i=0; i<=argpointer; i++){
                argstride+=argspace.at(i);
            }
            return argstride;
        }
        void restartSpacing(){
            argsused=0;
            argpointer=0;
        }
        std::vector<float> rawsetup(std::vector<Coor3D> coors){
            vertexs.clear();
            for (auto& coor : coors){
                pushCoor3D(vertexs, coor);
            }
            reserveArgSpace();
            return vertexs;
        }
        std::vector<float> addColor(std::vector<float>&vertexs, unsigned int vnum, RGBColor color){
            //std::cout << "Numero de vertices: " << vnum << std::endl;
            vertexcolors.clear();           //Limpio primero que nada
            int stride = calculateStride(); //Stride
            for(int i=0; i<vnum; i++){
                //std::cout << "Insertando en index: " << (3 + i* offset) << std::endl;
                insertColorAt(vertexs, color, argsused+i*stride);
                pushColor(vertexcolors, color);
            }
            reserveArgSpace();          
            return vertexs;
        }
        std::vector<float> padCoors(std::vector<float>&vertexs, unsigned int vnum, std::vector<Coor3D>&coors){
            int stride = calculateStride();
            for(int i=0; i<vnum; i++){
                //std::cout << "Insertando en index: " << (3 + i* stride) << std::endl;
                insertCoor3DAt(vertexs, coors.at(i), argsused+i*stride);
            }
            reserveArgSpace();
            return vertexs;
        }
    public:
        Player()=default;
        Player(Engine* engine, Shader* shader, float size, float radiusPos, float rotation, RGBColor playerColor):
            engine(engine),
            ShaderPlayer(shader)
        {
            std::cout<<"Oh me creooo, dice Player"<<std::endl;
            initShaders();
            this->scale=size;
            this->rotation=rotation;
            this->radiusPos=radiusPos;
            pcolor=playerColor;
            //vertices
            vertexs=rawsetup(vcoors);
            vertexs=addColor(vertexs,vertexs.size()/3,playerColor);
            vertexs=padCoors(vertexs,vertexs.size()/6,vcoors);
            //Memoria del objeto
            IDs.push_back(engine->createBuffer(vertexs,&indexes,9,argspace));
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
        const std::vector<float>&getVertexs() const {
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
};

#endif