#ifndef WALL_HPP
#define WALL_HPP

#include "Center.hpp"

#include <iostream>
#include <vector>

class Wall : public Center {
    private:
        std::vector<unsigned int> IDs={};           //Esto me permite saber que IDs tienen cada forma que vaya a renderizar
        std::vector<unsigned int> argspace={3,3,3}; //Pos//Color//toPos
        unsigned int argsused=0;
        unsigned int argpointer=0;

        std::vector<unsigned int> indexes={         //Indices de generacion
            0,1,2,
            0,2,3
        };
        std::vector<Coor3D> refcoors={};            //Coordenadas de referencia
        std::vector<RGBColor> vertexcolors={};      //Gama de colores POR VERTICE

        //General
        unsigned int indexPos=0;                    //Posicion con respecto al escenario (Util para el spawneo)
        float radiusPosOffset=10.0f;                //Posicion de aparicion de los obstaculos
        float marginL=0.05f;                        //Grosor izquierdo
        float marginR=0.05f;                        //Grosor derecho
        std::vector<RGBColor> wallcolors;           //Color principal (por vertice)
        //Transformaciones
        glm::mat4 model = glm::mat4(1.0f);
        //Objetos de referencia
        Engine* engine;
        Shader* ShaderWall;
        void setupWall(unsigned int index, std::vector<Coor3D> refcoors){
            refcoors.clear();
            if(index<(vnumber-1)){
                refcoors.push_back(wvcoors.at(index+1));
                refcoors.push_back(wvcoors.at(index+2));
            }else if(index=vnumber){
                refcoors.push_back(wvcoors.at(index));
                refcoors.push_back(wvcoors.at(1));
            }
        }
        

    public:
        Wall()=default;
        Wall(Engine* engine, Shader* shader, unsigned int indexPos, float margin_left, float margin_right, std::vector<RGBColor> wallcolors):
            engine(engine),
            ShaderWall(shader)
        {
            this->indexPos=indexPos;
            this->wallcolors=wallcolors;
            marginL=margin_left;
            marginR=margin_right;
        }
};

#endif