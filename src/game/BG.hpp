#ifndef BG_HPP
#define BG_HPP

#include "GEngine/Engine.hpp"
#include "GEngine/Shaders.hpp"
#include "BGType.hpp"
#include "Color.h"

#include <vector>
#include <cmath>
#include <iostream>

struct Coor3D {
    float x;
    float y;
    float z;
};

/*
struct RGBColor {
    float R;
    float G;
    float B;
};

enum class Type {
    CLASSIC,
    INDEXED
};
*/

class BG{
    private:
        //Variables propias de la clase
        std::vector<float> vertexs={};
        std::vector<unsigned int> indexes={};
        unsigned int vnumber = 3;
        float radius=1.2f;
        //Colores
        std::vector<RGBColor> pcolors={};
        //Objectos usados
        Engine engine;
        //Metodos
        void pushColor(RGBColor color){
            vertexs.push_back(color.R);
            vertexs.push_back(color.G);
            vertexs.push_back(color.B);
        }
        void insertColorAt(RGBColor color, int offset){
            vertexs.insert(vertexs.begin()+offset, color.R);
            vertexs.insert(vertexs.begin()+offset+1, color.G);
            vertexs.insert(vertexs.begin()+offset+2, color.B);
        }
        void pushCoor3D(Coor3D coors){
            vertexs.push_back(coors.x);
            vertexs.push_back(coors.y);
            vertexs.push_back(coors.z);
        }
        void pushCoor3DWRGB(Coor3D coor, RGBColor color){
            pushCoor3D(coor);
            pushColor(color);
        }
        void pushVTriangle(float a, float b, float c){
            indexes.push_back(a);
            indexes.push_back(b);
            indexes.push_back(c);
        }
        void pushTriangle(Coor3D A, Coor3D B, Coor3D C){
            pushCoor3D(A);
            pushCoor3D(B);
            pushCoor3D(C);
        }
        std::vector<float> setRegular(float radius, unsigned int vnumber){
            vertexs.clear();
            Coor3D currentcoor;
            currentcoor.x=0.0f;
            currentcoor.y=0.0f;
            currentcoor.z=0.0f;
            float anglex = (float)(4*acos(0.0)/vnumber);
            pushCoor3D(currentcoor);
            for (int i=0; i<vnumber; i++){
                currentcoor.x=radius*cos(anglex*i);
                currentcoor.y=radius*sin(anglex*i);
                pushCoor3D(currentcoor); 
            }
            return vertexs;
        }
        std::vector<float> rawsetRegular(float radius, unsigned int vnumber){
            vertexs.clear();
            std::vector<Coor3D> tempv={};
            Coor3D currentcoor;
            currentcoor.x=0.0f;
            currentcoor.y=0.0f;
            currentcoor.z=0.0f;
            float anglex = (float)(4*acos(0.0)/vnumber);
            tempv.push_back(currentcoor);
            for (int i=0; i<vnumber; i++){
                currentcoor.x=radius*cos(anglex*i);
                currentcoor.y=radius*sin(anglex*i);
                tempv.push_back(currentcoor);
            }
            vertexs=createTriangles(tempv);

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
        std::vector<float> createTriangles(std::vector<Coor3D>coors){
            for(int i=1; i<(coors.size()-1); i++){
                pushTriangle(coors.at(0), coors.at(i), coors.at(i+1));
            }
            pushTriangle(coors.at(0), coors.at(coors.size()-1), coors.at(1));
            return vertexs;
        }
        std::vector<float> addColors(unsigned int vnum, std::vector<RGBColor>&colors){
            int offset = 6;
            int checkin = 0;
            for(int i=0; i<vnum; i++){
                insertColorAt(setColorPattern(checkin, 3, colors), 3+i*offset);
                checkin++;
            }
            return vertexs;
        }
        RGBColor setColorPattern(int check, unsigned int timesto, std::vector<RGBColor>&colors){
            if (colors.empty() || timesto == 0) return RGBColor{0.0f, 0.0f, 0.0f};
            int index = (check / timesto) % colors.size();
            RGBColor currentColor = colors.at(index);
            return currentColor;
        }
    public:
        //Constructors
        BG()=default;
        BG(float radius, unsigned int vnum, std::vector<RGBColor>&colors, Type type):
            engine()
        {
            pcolors = colors;
            vnumber = vnum;
            if(type==Type::INDEXED){
                vertexs = setRegular(radius, vnum);
                indexes = createIndexes(vnum);
            }else if (type==Type::CLASSIC){
                vertexs = rawsetRegular(radius, vnum);
                vertexs = addColors(vertexs.size()/3, colors);
            }
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
        void show(unsigned int rVAO) {
            //float time = glfwGetTime();
            //int colorIndex = static_cast<int>(time) % colors.size();
            engine.renderPolygon2(rVAO, getVertexs().size());
        }
};

#endif