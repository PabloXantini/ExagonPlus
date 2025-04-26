#ifndef WALL_HPP
#define WALL_HPP

#include "Center.hpp"

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
        float timesto=4;
        std::vector<RGBColor> wallcolors;               //Color principal (por vertice)
        //Transformaciones
        glm::mat4 model = glm::mat4(1.0f);
        //Objetos de referencia
        Engine* engine;
        Shader* ShaderWall;
        Center* center;
        //Methods
        /*
            Inicializacion de Shader
        */
        void initShaders(){
            //ShaderBG = new Shader(IDR_VSHADER2,IDR_FSHADER2);
            //std::cout << "ShaderBG ptr: " << ShaderBG << std::endl;
            //Inicializacion
            ShaderBG->setFloat("collapseprogress",0.0f);
        }
        void setupWall(unsigned int index, std::vector<Coor3D>& refcoors){
            refcoors.clear();
            std::vector<Coor3D> coors = center->get3DCoors();
            if(index<(vnumber-1)){
                refcoors.push_back(coors.at(index+1));
                refcoors.push_back(coors.at(index+2));
            }else if(index=vnumber){
                refcoors.push_back(coors.at(index));
                refcoors.push_back(coors.at(1));
            }
            //Construir los otros lados
            refcoors.push_back(refcoors.at(1));
            refcoors.push_back(refcoors.at(0));
        }
        void addColors(unsigned int vnum, unsigned int timesto, std::vector<RGBColor>&colors){
            //std::cout << "Numero de vertices: " << vnum << std::endl;
            vertexcolors.clear();           //Limpio primero que nada
            int checkin = 0;
            RGBColor newColor;
            for(int i=0; i<vnum; i++){
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
            std::cout<<"Oh me creooo, no puso pared"<<std::endl;
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
        /*
            Renderizar/Mostrar
        */
        void show() {
            ShaderWall->setInt("ObjectType", 1);
            ShaderWall->setFloat("MarginL",marginL);
            ShaderWall->setFloat("MarginR",marginR);
            ShaderWall->setMat4("Model", model);
            engine->renderPolygon(ShaderWall, this->getID(0), indexes.size());
        }
};

#endif