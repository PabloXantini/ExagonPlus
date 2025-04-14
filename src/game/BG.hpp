#ifndef BG_HPP
#define BG_HPP

#include "GEngine/Engine.hpp"
#include "GEngine/Shaders.hpp"

#include <vector>
#include <cmath>
#include <iostream>

class BG{
    private:
        //Variables propias de la clase
        std::vector<float> vertexs={};
        std::vector<unsigned int> indexes={};
        unsigned int vnumber = 3;
        float radius=1.2f;    
        //Objectos usados
        Engine engine;
        void pushCoors(float x, float y, float z){
            vertexs.push_back(x);
            vertexs.push_back(y);
            vertexs.push_back(z);
        }
        void pushVTriangle(float a, float b, float c){
            indexes.push_back(a);
            indexes.push_back(b);
            indexes.push_back(c);
        }
        std::vector<float> setRegular(float radius, unsigned int vnumber){
            vertexs.clear();
            float x=0.0f;
            float y=0.0f;
            float z=0.0f;
            float anglex = (float)(4*acos(0.0)/vnumber);
            pushCoors(x, y, z);
            for (int i=0; i<vnumber; i++){
                x=radius*cos(anglex*i);
                y=radius*sin(anglex*i);
                pushCoors(x, y, z); 
            }
            return vertexs;
        }
        std::vector<unsigned int> createIndexes(unsigned int vnumber){
            indexes.clear();
            for(int i=1; i<vnumber; i++){
                pushVTriangle(0, i, i+1);
            }
            pushVTriangle(0, vnumber, 1);
            return indexes;
        }
    public:
        //Constructors
        BG()=default;
        BG(float radius, unsigned int vnum){
            vertexs = setRegular(radius, vnum);
            indexes = createIndexes(vnum);
            vnumber = vnum;
        }

        //Getters
        const std::vector<float>&getVertexs() const {
            return vertexs;
        }
        const std::vector<unsigned int>&getIndexes() const {
            return indexes;
        }
        const unsigned int getVertexCount() const {
            unsigned int vnum = vnumber+1;
            return vnum;
        }
        //Setters
        void setVertexs(std::vector<float> vxs) {
            vertexs=vxs;
        }
        //Mostrar
        void show(unsigned int rVAO){
            //float time = glfwGetTime();
            //int colorIndex = static_cast<int>(time) % colors.size();
            engine.renderPolygon(rVAO, getIndexes().size());
        }
};

#endif