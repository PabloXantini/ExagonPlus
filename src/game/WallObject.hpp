#ifndef WALL_OBJECT_HPP
#define WALL_OBJECT_HPP

#include "utils/Color.h"
#include "AnimationMaker.hpp"
#include "Wall.hpp"

#include <iostream>
#include <vector>

class CompleteWall {
    private:
        //Punteros de funciones
        std::function<void(Animation*, float)>movW = std::bind(&CompleteWall::collapseWall, this, std::placeholders::_1, std::placeholders::_2);
        //Variables propias de la clase
        bool alive=false;                               //Indica si esta activo
        float animfactor=2.0f;                          //Easing/Exp Factor (En un futuro)
        unsigned int timesto;                           //Veces que se pinta el color
        float marginL=0.05f;                            //Grosor izquierdo
        float marginR=0.05f;                            //Grosor derecho
        std::vector<RGBColor> wallcolors = {};          //Colores de las paredes
        std::vector<RGBColor> wallcolorsc = {};         //Colores de las paredes (copia)
        std::vector<unsigned int> wallindexes={0,2,4};  //Indices al gusto
        std::vector<Wall> walls={};                    //Las paredes
        //Objetos de referencia
        Engine* engine;
        Shader* shader;
        Center* center;
        //Objetos usados
        Animation animation;
        //Methods
        /*
            Crea las paredes segun el indice
        */
        void setupWalls(std::vector<unsigned int> indexes){
            size_t numi = indexes.size();
            unsigned int sides = center->getSides();
            bool manyWalls = numi>=sides;
            unsigned int exit = 0;
            if(manyWalls) exit = indexes.at(rand()%sides);
            for(auto& index : indexes){
                //Condicion que siempre se aplica cuando los espacios estan llenos
                if(manyWalls&&index==exit) continue;
                walls.emplace_back(engine, shader, center, index, marginL, marginR, timesto, setColorPattern(index));
            }
        }
        /*
            Estalbece un color en carrusel
        */
        std::vector<RGBColor> setColorPattern(unsigned int pos){
            std::vector<RGBColor> colors;
            if (wallcolorsc.empty()) return colors = {{0.0f, 0.0f, 0.0f}};
            colors = wallcolorsc;
            unsigned int offset = pos % colors.size();
            std::rotate(colors.begin(), colors.begin()+offset, colors.end());
            return colors;
        }
    public:
        CompleteWall()=default;
        CompleteWall(Engine* engine, Shader* shader, Center* center, float duration, float easing, AnimType animtype, std::vector<unsigned int> indexes, float marginL, float marginR, std::vector<RGBColor> wallcolors, unsigned int timestopattern):
            engine(engine),
            shader(shader),
            center(center),
            animation(duration, easing, movW, animtype)
        {
            wallindexes=indexes;
            this->wallcolors=wallcolors;
            wallcolorsc=wallcolors;
            this->marginL=marginL;
            this->marginR=marginR;
            timesto=timestopattern;
            alive=true;
            setupWalls(indexes);
        }
        CompleteWall(Engine* engine, Shader* shader, Center* center, float duration, AnimType animtype, std::vector<unsigned int> indexes, float marginL, float marginR, std::vector<RGBColor> wallcolors, unsigned int timestopattern):
            engine(engine),
            shader(shader),
            center(center),
            animation(duration, movW, animtype)
        {
            wallindexes=indexes;
            this->wallcolors=wallcolors;
            wallcolorsc=wallcolors;
            this->marginL=marginL;
            this->marginR=marginR;
            timesto=timestopattern;
            alive=true;
            setupWalls(indexes);
        }
        ~CompleteWall(){
            //std::cout<<"Tu papa te abandonoo"<<std::endl;
            for(Wall& wall : walls){
                wall.kill();     
            }
            walls.clear();
        }
        //Getters
        bool isAlive(){
            return alive;
        }
        std::vector<Wall>& getWalls(){
            return walls;
        }
        /*
            Muestra las paredes a la vez
        */
        void show(){
            for (auto& wall : walls){
                wall.show();
            }
        }
        /*
            Dispara el movimiento de la pared
        */
        void execute(float step){
            animation.execute(step);
        }
        /*
            Callback para mover la pared
        */
        void collapseWall(Animation* anim, float deltamov){
            for(Wall& wall : walls){
                wall.collapse(deltamov);
            }
            if(deltamov==1.0f){
                for(Wall& wall : walls){
                    wall.kill();
                    //delete wall;
                }
                walls.clear();
                alive=false;
            }
        }
};

#endif