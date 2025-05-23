#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GEngine/Engine.hpp"
#include "GEngine/Shader.hpp"
#include "utils/Vertex.h"
#include "utils/Position.h"
#include "utils/Color.h"
#include "BG.hpp"

#include <iostream>
#include <cmath>
#include <vector>

class Player : public BG {
    private:
        std::vector<unsigned int> IDs={};                   //Esto me permite saber que IDs tienen cada forma que vaya a renderizar
        std::vector<unsigned int> argspace={3,3,3,3};       //Pos//Color//toPos//Color2
        std::vector<unsigned int> indexes={0,1,3,1,2,3};    //Indices de generacion
        //std::vector<float> vertexs={};                    //Vertices brutos del objeto
        std::vector<WVertex3D> vertexs={};                  //Vertices brutos del objeto

        std::vector<RGBColor> vertexcolors={};              //Gama de colores POR VERTICE

        std::vector<Coor3D> vcoors={                        //Coordenadas 3D POR VERTICE
            {-0.01f, -0.01f, 0.0f},
            {0.0f, 0.01f, 0.0f},
            {0.01f, -0.01f, 0.0f},
            {0.0f, -0.005f, 0.0f}
        };
        //General
        bool liveStatus = true;
        float sensibility = 100.0f;
        float radiusPos = 0.6f;
        float rotationInit = 0.0f;
        float scale = 1.0f;
        float rotation = 0.0f;
        //Color
        RGBColor pcolor;
        //Transformaciones
        glm::mat4 model = glm::mat4(1.0f);
        //Trackeo de posicion
        std::vector<glm::vec3> baseposes={};                //Inicializado
        std::vector<glm::vec3> poses={};                    //Verdaderos usados como posiciones dinamicas
        //Objetos de referencia
        Engine* engine;
        Shader* ShaderPlayer;
        //Metodos de creacion
        void initShaders(){
            //Incializacion del shader
        }
        void setPos(){
            //Solo considera las primeras 3 coordenadas por simplicidad
            for(int i=0; i<3; i++){
                baseposes.push_back(glm::vec3(model*glm::vec4(parseToVec3(vcoors.at(i)),1.0f)));
            }
            //Copio a posiciones dinamicas
            poses=baseposes;
        }
        void changePos(){
            poses.clear();
            //Una transformacion distinta
            glm::mat4 trans = glm::mat4(1.0f);
            trans = glm::rotate(trans, glm::radians(rotation-rotationInit), glm::vec3(0.0,0.0,1.0));
            for(const auto& pos : baseposes){
                poses.push_back(glm::vec3(trans*glm::vec4(pos,1.0f)));
            }
        }
        void addColor( unsigned int vnum, RGBColor color){
            //std::cout << "Numero de vertices: " << vnum << std::endl;
            vertexcolors.clear();           //Limpio primero que nada
            for(unsigned int i=0; i<vnum; i++){
                //std::cout << "Insertando en index: " << (3 + i* offset) << std::endl;
                pushColor(vertexcolors, color);
            }
        }
        void rotatePlayerPos(float step){
            rotation+=step;
            //Clampear la rotacion
            rotation=normalizeAngle(rotation);
            //Transformacion
            model = glm::mat4(1.0f);    //Reiniciar la transformacion
            model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0,0.0,1.0));
            model = glm::translate(model, glm::vec3(radiusPos,0.0,0.0));
            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0,0.0,1.0));
            model = glm::scale(model, glm::vec3(scale));
            changePos();
        }
        void collidePlayerPos(glm::vec3 direction){
            float epsilon = 1.5f;
            //Obtener el vector de rotacion
            glm::vec3 radial = getRotVector(rotation);
            float ProjDtoR = glm::dot(radial, direction);       //Proyeccion de direccion respecto al radial
            //Obtener el vector rotacional
            glm::vec3 ProjRot = ProjDtoR * radial;
            glm::vec3 TanRot = epsilon*(direction - ProjRot);

            //Convertir la fuerza en una rotacion polar
            float step = glm::degrees(glm::length(TanRot))/radiusPos;
            if(glm::cross(radial, TanRot).z<0) step*=-1.0f;
            //Aplicar la rotacion de nuevo
            rotatePlayerPos(step);
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
            this->rotationInit=rotation;
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
            //Posicion verdadera
            setPos();
            //SOLO DEBUG
            /*
            IDs.push_back(engine->createBuffer(poses,NULL,3,std::vector<unsigned int>{3}));
            */
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
        std::vector<glm::vec3>&getPos() {
            return poses;
        }
        bool isAlive(){
            return liveStatus;
        }
        //Setters
        void setLiveStatus(bool state){
            liveStatus=state;
        }
        /*
            Renderizar/Mostrar
        */
        void show() {
            ShaderPlayer->setInt("ObjectType", 0);
            ShaderPlayer->setMat4("Model", model);
            engine->renderPolygon(ShaderPlayer, this->getID(0), indexes.size());
            //SOLO DEBUG
            /*
            ShaderPlayer->setInt("ObjectType", 2);
            ShaderPlayer->setMat4("Model", glm::mat4(1.0f));
            engine->renderLasso(ShaderPlayer, this->getID(1), poses.size());
            */
        }
        /*
            Mover
        */
        void move(float step) {
            rotatePlayerPos(step);
            //SOLO DEBUG
            /*
            engine->modBuffer(this->getID(1), poses, NULL);
            */
        }
        /*
            Colisiona
        */
        void collide(glm::vec3 direction) {
            collidePlayerPos(direction);
            //SOLO DEBUG
            /*
            engine->modBuffer(this->getID(1), poses, NULL);
            */
        }
        /*
            Libera memoria de GPU
        */
        void free(){
            engine->eliminateBuffer(this->getID(0));
            //SOLO DEBUG
            /*
            engine->eliminateBuffer(this->getID(1));
            */
        }
};

#endif