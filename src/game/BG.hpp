#ifndef BG_HPP
#define BG_HPP

#include "Engine.hpp"
#include "Shaders.hpp"

#include <vector>
#include <cmath>
#include <iostream>

class BG{
    private:
        //Variables propias de la clase
        std::vector<float> vertexs={};
        unsigned int vnumber = 3;
        float radius=1.2f;
        //Objectos usados
        Engine engine;
        void pushCoors(float x, float y, float z){
            vertexs.push_back(x);
            vertexs.push_back(y);
            vertexs.push_back(z);
        }
        std::vector<float> setRegular(float radius, unsigned int vnumber){
            vertexs.clear();
            float x=0.0f;
            float y=0.0f;
            float z=0.0f;
            float anglex = (float)(4*acos(0.0)/vnumber);
            for (int i=0; i<vnumber; i++){
                x=radius*cos(anglex*i);
                y=radius*sin(anglex*i);
                pushCoors(x, y, z); 
            }
            return vertexs;
        }
    public:
        //Constructors
        BG()=default;
        BG(float radius, unsigned int vnum){
            vertexs = setRegular(radius, vnum);
            vnumber = vnum;
        }

        //Getters
        const std::vector<float>&getVertexs() const {
            return vertexs;
        }
        const unsigned int&getVertexCount() const {
            return vnumber;
        }
        //Setters
        void setVertexs(std::vector<float> vxs) {
            vertexs=vxs;
        }
        //Mostrar
        void show(unsigned int rVAO){
            engine.renderPolygon(rVAO, engine.getShaderProgram(BASIC), getVertexCount());
        }
};

#endif