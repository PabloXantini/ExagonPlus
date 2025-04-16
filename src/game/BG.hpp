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

class BG{
    private:
        //Variables propias de la clase
        //Graficos
        std::vector<unsigned int> IDs={};       //Esto me permite saber que IDs tienen cada forma que vaya a renderizar
        std::vector<float> vertexs={};          //Vertices del objeto
        std::vector<unsigned int> indexes={};   //Indices de generacion
        //General
        unsigned int timesto = 3;               //Veces en la que se reproducir el patron
        unsigned int vnumber = 3;               //Lados del escenario               
        float radius=1.2f;                      //Es para setear el largo del escenario
        std::vector<RGBColor> pcolors={};       //Gama de colores
        //Objectos usados
        Engine* engine;
        //Metodos
        void pushColor(RGBColor color){
            vertexs.push_back(color.R);
            vertexs.push_back(color.G);
            vertexs.push_back(color.B);
        }
        void pushColor(std::vector<float>&vertexs, RGBColor color){
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
        void pushCoor3D(std::vector<float>&vertexs, Coor3D coors){
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
        std::vector<float> addColors(unsigned int vnum, unsigned int timesto, std::vector<RGBColor>&colors){
            std::cout << "Numero de vertices: " << vnum << std::endl;
            //std::vector<float> newVertexs;
            //Coor3D coorcopy;
            //RGBColor c;
            int offset = 6;
            int checkin = 0;
            for(int i=0; i<vnum-timesto; i++){
                std::cout << "Insertando en index: " << (3 + i* offset) << std::endl;
                insertColorAt(setColorPattern(checkin, timesto, colors), 3+i*offset);
                //Define el ultimo color si el poligono es par
                checkin++;
            }
            if((vnum/3)%2==0){
                for(int i=0;i<timesto;i++){
                    std::cout << "Insertando en index: " << (3 +(vnum-timesto+i)* offset) << std::endl;
                    insertColorAt(setColorPattern(checkin, timesto, colors), 3+(vnum-timesto+i)*offset);
                    std::cout << "Paso la prueba " << std::endl;
                    checkin++;
                }
            }else{
                for(int i=0;i<timesto;i++){
                    std::cout << "Insertando en index: " << (3 +(vnum-timesto+i)* offset) << std::endl;
                    insertColorAt(colors.back(), 3+(vnum-timesto+i)*offset);
                    std::cout << "Paso la prueba " << std::endl;
                }
            }
            return vertexs;
        }
        RGBColor setColorPattern(int check, unsigned int timesto, std::vector<RGBColor>&colors){
            if (colors.empty() || timesto == 0) return RGBColor{0.0f, 0.0f, 0.0f};
            int index = (check / timesto) % (colors.size()-1);
            RGBColor currentColor = colors.at(index);
            return currentColor;
        }

    public:
        //Constructors
        BG()=default;
        BG(Engine* engine, float radius, unsigned int vnum, unsigned int patterntimesto, std::vector<RGBColor>&colors, Type type):
            engine(engine)
        {
            std::cout<<"Oh me creooo, dice BG"<<std::endl;
            pcolors = colors;
            vnumber = vnum;
            timesto = patterntimesto;
            if(type==Type::INDEXED){
                vertexs = setRegular(radius, vnum);
                indexes = createIndexes(vnum);
                //Memoria del objeto
                IDs.push_back(engine->createBuffer3D(vertexs, &indexes, false).VAO);
            }else if (type==Type::CLASSIC){
                vertexs = rawsetRegular(radius, vnum);
                vertexs = addColors(vertexs.size()/3, timesto, colors);
                //Memoria del objeto
                IDs.push_back(engine->createBuffer3D(vertexs, NULL, true).VAO);
            }
            //Comentalo si quieres
            std::cout << "[ ";
            for (float val : vertexs) {
                std::cout << val << " ";
            }
            std::cout << "]" << std::endl;
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
        const unsigned int getVertexCount() const {
            unsigned int vnum = vnumber+1;
            return vnum;
        }
        //Setters
        void setVertexs(std::vector<float> vxs) {
            vertexs=vxs;
        }
        //Mostrar
        void show() {
            engine->renderPolygon2(this->getID(0), getVertexs().size());
        }
};

#endif