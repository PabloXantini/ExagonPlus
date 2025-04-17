#ifndef BG_HPP
#define BG_HPP

#include "GEngine/Engine.hpp"
#include "GEngine/Shaders.hpp"
#include "BGType.hpp"
#include "Color.h"

#include <algorithm>
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
        std::vector<RGBColor> vertexcolors={};  //Gama de colores POR VERTICE
        std::vector<RGBColor> pcolors={};       //Gama de colores
        //Objectos de referencia
        Engine* engine;
        //Metodos de creacion
        /*
            Añade un color a la mezcla de vertices
        */
        void pushColor(RGBColor color){
            vertexs.push_back(color.R);
            vertexs.push_back(color.G);
            vertexs.push_back(color.B);
        }
        /*
            Añade un color a la mezcla de vertices, en base a un vector determinado
            void pushColor(std::vector<float>&vertexs, RGBColor color){
                vertexs.push_back(color.R);
                vertexs.push_back(color.G);
                vertexs.push_back(color.B);
            }
        */
        /*
            Añade un color a la mezcla de vertices, en base a un vector de Colores determinado
        */
        void pushColor(std::vector<RGBColor>&colors, RGBColor color){
            colors.push_back(color);
        }
        /*
            Añade un color a la mezcla de vertices, dependiendo del desplazamiento
        */
        void insertColorAt(RGBColor color, int offset){
            vertexs.insert(vertexs.begin()+offset, color.R);
            vertexs.insert(vertexs.begin()+offset+1, color.G);
            vertexs.insert(vertexs.begin()+offset+2, color.B);
        }
        /*
            Añade una coordenada 3D
        */
        void pushCoor3D(Coor3D coors){
            vertexs.push_back(coors.x);
            vertexs.push_back(coors.y);
            vertexs.push_back(coors.z);
        }
        /*
            Añade una coordenada 3D, en base a un vector determinado
        */
        void pushCoor3D(std::vector<float>&vertexs, Coor3D coors){
            vertexs.push_back(coors.x);
            vertexs.push_back(coors.y);
            vertexs.push_back(coors.z);
        }
        /*
            Añade una coordenada 3D y un color a la vez al conjunto de vértices
        */
        void pushCoor3DWRGB(Coor3D coor, RGBColor color){
            pushCoor3D(coor);
            pushColor(color);
        }
        /*
            Inserta un triangulo al conjunto de indices
        */
        void pushVTriangle(float a, float b, float c){
            indexes.push_back(a);
            indexes.push_back(b);
            indexes.push_back(c);
        }
        /*
            Inserta un triangulo indicado por las coordenadas del triangulo
        */
        void pushTriangle(Coor3D A, Coor3D B, Coor3D C){
            pushCoor3D(A);
            pushCoor3D(B);
            pushCoor3D(C);
        }
        /*
            Guarda datos escenciales para el trazado del escenario (traza un poligono regular), usando indices
        */
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
        /*
            Crea los indices, con lo que se va trazar cada triangulo de manera INDEXED
        */
        std::vector<unsigned int> createIndexes(unsigned int vnumber){
            indexes.clear();
            for(int i=1; i<vnumber; i++){
                pushVTriangle(0, i, i+1);
            }
            pushVTriangle(0, vnumber, 1);
            return indexes;
        }
        /*
            Guarda datos escenciales para el trazado del escenario (traza un poligono regular), con vertices puros
        */
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
        /*
            Crea los triangulos de manera bruta para la manera CLASSIC
        */
        std::vector<float> createTriangles(std::vector<Coor3D>coors){
            for(int i=1; i<(coors.size()-1); i++){
                pushTriangle(coors.at(0), coors.at(i), coors.at(i+1));
            }
            pushTriangle(coors.at(0), coors.at(coors.size()-1), coors.at(1));
            return vertexs;
        }
        /*
            Inserta los colores en las coordenadas de las posiciones con algo de estilo
        */
        std::vector<float> addColors(unsigned int vnum, unsigned int timesto, std::vector<RGBColor>&colors){
            //std::cout << "Numero de vertices: " << vnum << std::endl;
            int offset = 6;
            int checkin = 0;
            RGBColor newColor;
            for(int i=0; i<vnum-timesto; i++){
                //std::cout << "Insertando en index: " << (3 + i* offset) << std::endl;
                newColor = setColorPattern(checkin, timesto, colors);
                insertColorAt(newColor, 3+i*offset);
                pushColor(vertexcolors, newColor);
                checkin++;
            }
            //Define el ultimo color si el poligono es par
            if((vnum/3)%2==0){
                for(int i=0;i<timesto;i++){
                    //std::cout << "Insertando en index: " << (3 +(vnum-timesto+i)* offset) << std::endl;
                    newColor = setColorPattern(checkin, timesto, colors);
                    insertColorAt(newColor, 3+(vnum-timesto+i)*offset);
                    pushColor(vertexcolors, newColor);
                    checkin++;
                }
            }else{
                //pushColor(vertexcolors, colors.back());
                for(int i=0;i<timesto;i++){
                    //std::cout << "Insertando en index: " << (3 +(vnum-timesto+i)* offset) << std::endl;
                    newColor = colors.back();
                    insertColorAt(newColor, 3+(vnum-timesto+i)*offset);
                    pushColor(vertexcolors, newColor);
                }
            }
            return vertexs;
        }
        /*
            Establece el patron de los colores, 3 se usa para imprimir los triangulos de un solo color, mas o menos generan gradientes
        */
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
        const std::vector<RGBColor>&getColors() const {
            return pcolors;
        }
        //Setters
        void setVertexs(std::vector<float> vxs) {
            vertexs=vxs;
        }
        //Mostrar
        void show() {
            engine->renderPolygon2(this->getID(0), getVertexs().size());
        }
        /*
            Intercambia los colores de BG con los de su vecino
        */
        void swapColors(){
            std::rotate(vertexcolors.begin(), vertexcolors.begin()+timesto, vertexcolors.end());
            engine->updateBufferColorWeight(this->getID(0), vertexcolors);
        }
        /*
            Cambia el HUE del escenario
        */
        void changeBGHue(float time, float BGHueFactor, float BGHueSpeed){
            engine->changeHue(time, BGHueFactor, BGHueSpeed);
        }
};

#endif