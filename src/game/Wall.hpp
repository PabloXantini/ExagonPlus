#ifndef WALL_HPP
#define WALL_HPP

#include "Center.hpp"
#include "AnimationMaker.hpp"

#include <iostream>
#include <vector>

class Wall : public Center {
    private:
        std::vector<unsigned int> IDs={};               //Esto me permite saber que IDs tienen cada forma que vaya a renderizar
        std::vector<unsigned int> argspace={3,3,3,3};   //Pos//Color//toPos
        
        std::vector<WVertex3D> vertexs={};              //Vertices brutos del objeto           
        std::vector<unsigned int> indexes={             //Indices de generacion
            0,1,2,
            0,2,3
        };
        std::vector<Coor3D> refcoors={};                //Coordenadas de referencia (Origen)
        std::vector<Coor3D> torefcoors={};              //Coordenadas de referencia (Destino)
        std::vector<RGBColor> vertexcolors={};          //Gama de colores POR VERTICE

        //General
        unsigned int indexPos=0;                        //Posicion con respecto al escenario (Util para el spawneo)
        float radiusPosOffset=10.0f;                    //Posicion de aparicion de los obstaculos
        float marginL=0.05f;                            //Grosor izquierdo
        float marginR=0.05f;                            //Grosor derecho
        unsigned int timesto=4;
        std::vector<RGBColor> wallcolors;               //Color principal (por vertice)
        //Transformaciones
        float step = 0.0f;
        glm::mat4 model = glm::mat4(1.0f);
        //Trackeo de posicion
        std::vector<glm::vec3> baseposes = {};          //Inicializado
        std::vector<glm::vec3> poses = {};              //Verdaderos usados como posiciones dinamicas
        //Objetos de referencia
        Engine* engine;
        Shader* ShaderWall;
        Center* center;
        //Methods
        /*
            Inicializacion de Shader
        */
        void initShaders(){
            //Inicializacion
        }
        /*
            Setea la posicion
        */
        void setPos(){
            baseposes.clear();
            for (auto& refcoor : refcoors){
                baseposes.push_back(parseToVec3(refcoor));
            }
            for (auto& pos : baseposes){
                pos*=14.0f;
            }
            poses=baseposes;
        }
        void collapsePos(){
            std::vector<glm::vec3> normals;
            for (size_t i=0; i<poses.size()-2; i++){
                normals.push_back(glm::normalize(baseposes.at(i)));
                poses.at(i)=glm::mix(baseposes.at(i), glm::vec3(0.0f), step);              
            }
            poses.at(2)=poses.at(1)+normals.at(1)*marginR;
            poses.at(3)=poses.at(0)+normals.at(0)*marginL;
        } 
        /*
            Setea la pared
        */
        void setupWall(unsigned int index, std::vector<Coor3D>& refcoors){
            refcoors.clear();
            unsigned int sides = center->getSides();
            std::vector<Coor3D> coors = center->get3DCoors();
            if(index<(sides-1)){
                refcoors.push_back(coors.at(index+1));
                refcoors.push_back(coors.at(index+2));
            }else {
                refcoors.push_back(coors.at(sides));
                refcoors.push_back(coors.at(1));
            }
            //Construir los otros lados
            refcoors.push_back(refcoors.at(1));
            refcoors.push_back(refcoors.at(0));
            //Crea las verdaderas coordenadas
            setPos();
        }
        /*
            Setea la nueva posicion de la pared
        */
        std::vector<Coor3D> setNewWall(std::vector<Coor3D>& torefcoors, unsigned int vnumber){
            torefcoors.clear();
            std::vector<Coor3D> coors = center->get3DCoors();
            if(indexPos<(vnumber-1)){
                torefcoors.push_back(coors.at(indexPos+1));
                torefcoors.push_back(coors.at(indexPos+2));
            }else {
                torefcoors.push_back(coors.at(vnumber));
                torefcoors.push_back(coors.at(1));
            }
            //Construir los otros lados
            torefcoors.push_back(torefcoors.at(1));
            torefcoors.push_back(torefcoors.at(0));
            return torefcoors;
        }
        /*
            Aniade colores a la pared
        */
        void addColors(unsigned int vnum, unsigned int timesto, std::vector<RGBColor>&colors){
            //std::cout << "Numero de vertices: " << vnum << std::endl;
            vertexcolors.clear();           //Limpio primero que nada
            int checkin = 0;
            RGBColor newColor;
            for(unsigned int i=0; i<vnum; i++){
                //std::cout << "Insertando en index: " << (3 + i* offset) << std::endl;
                newColor = setColorPattern(checkin, timesto, colors);
                pushColor(vertexcolors, newColor);
                checkin++;
            }
        }

    public:
        Wall()=default;
        Wall(Engine* engine, Shader* shader, Center* center, unsigned int indexPos, float margin_left, float margin_right, unsigned int timestopattern, std::vector<RGBColor> wallcolors):
            engine(engine),
            ShaderWall(shader),
            center(center)
        {
            //std::cout<<"Oh me creooo, no puso pared"<<std::endl;
            this->indexPos=indexPos;
            this->wallcolors=wallcolors;
            marginL=margin_left;
            marginR=margin_right;
            timesto=timestopattern;
            //Pared
            setupWall(indexPos, refcoors);
            addColors(refcoors.size(), timesto, wallcolors);
            vertexs=setupMesh(refcoors, vertexcolors, refcoors, vertexcolors);
            torefcoors=refcoors;
            //Memoria del objeto
            IDs.push_back(engine->createBuffer(vertexs,&indexes,12,argspace));
            //SOLODEBUG
            IDs.push_back(engine->createBuffer(poses,NULL,3,std::vector<unsigned int>{3}));
        }
        ~Wall(){
            //std::cout<<"Y se marcho, y a su barco lo llamo libertad"<<std::endl;
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
        const std::vector<RGBColor>&getColors() const {
            return wallcolors;
        }
        std::vector<glm::vec3>&getPos() {
            return poses;
        }
        float getProgress() const {
            return step;
        }
        /*
            Renderizar/Mostrar
        */
        void show() {
            ShaderWall->setInt("ObjectType", 1);
            ShaderWall->setFloat("marginL",marginL);
            ShaderWall->setFloat("marginR",marginR);
            ShaderWall->setFloat("collapseprogress",step);
            ShaderWall->setMat4("Model", model);
            engine->renderPolygon(ShaderWall, this->getID(0), indexes.size());
            //SOLO DEBUG
            ShaderWall->setInt("ObjectType", 2);
            engine->renderLasso(ShaderWall, this->getID(1), poses.size());
        }
        /*
            Reserva la posicion para realizar el morphing
        */
        void prepareWallforDecrease(int sides){         
            //Valor temporal
            std::vector<Coor3D> refcoorsc = torefcoors;
            //Guardo nuevas coordenadas al buffer
            //Pared
            torefcoors=setNewWall(torefcoors, sides);
            vertexs=modMesh(vertexs, &refcoorsc, NULL, &torefcoors, NULL);
            engine->modBuffer(this->getID(0),vertexs, &indexes);
            //Preparo vertexs para temas de consistencia
            addColors(torefcoors.size(), timesto, wallcolors);
            vertexs=setupMesh(torefcoors, vertexcolors, torefcoors, vertexcolors);
        }
        
        void prepareWallforIncrease(int sides){
            //Valor temporal
            std::vector<Coor3D> refcoorsc = torefcoors;
            //Pared
            //Preparo vertexs para temas de consistencia
            torefcoors=setNewWall(torefcoors, sides);
            addColors(torefcoors.size(), timesto, wallcolors);
            vertexs=setupMesh(refcoorsc, vertexcolors, torefcoors, vertexcolors);
            //Escribo
            engine->updateBuffer(this->getID(0),vertexs, &indexes);
        }
        /*
            Actualiza solo al terminar (morphing)
        */
        void endUpdate(int sides){
            engine->updateBuffer(this->getID(0),vertexs, &indexes);
        }
        /*
            Mover pared
        */
        void collapse(float step){
            this->step=step;
            //Cambio de posicion
            collapsePos();
            //SOLO DEBUG
            engine->modBuffer(this->getID(1), poses, NULL);
        }
        void kill(){
            engine->eliminateBuffer(this->getID(0));
            //SOLO DEBUG
            engine->eliminateBuffer(this->getID(1));
        }
};

#endif