#ifndef BG_HPP
#define BG_HPP

#include "GEngine/Engine.hpp"
#include "GEngine/Shaders.hpp"
#include "Color.h"

#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>

enum class Type {
    CLASSIC,
    INDEXED
};

class BG{
    private:
        //Variables propias de la clase
        //Graficos
        std::vector<unsigned int> IDs={};           //Esto me permite saber que IDs tienen cada forma que vaya a renderizar
        std::vector<unsigned int> argspace={3,3,3}; //Pos//Color//toPos
        unsigned int argsused=0;
        unsigned int argpointer=0;

        std::vector<unsigned int> indexes={};       //Indices de generacion
        std::vector<float> vertexs={};              //Vertices brutos del objeto
        std::vector<float> dynamicvertexs={};       //Espacio dinamico en el que se guardan los vertices
        
        std::vector<Coor3D> vcoors={};              //Coordenadas 3D POR VERTICE
        std::vector<Coor3D> allvcoors={};           //Coordenadas 3D POR VERTICE
        std::vector<Coor3D> allvcoorscopy={};       //Copia Coordenadas 3D POR VERTICE
        std::vector<RGBColor> vertexcolors={};      //Gama de colores POR VERTICE
        //General
        std::vector<float> skvertexs={};            //Coordenadas generales (Util para heredar)
        unsigned int timesto = 3;                   //Veces en la que se reproducir el patron
        unsigned int vnumber = 3;                   //Lados del escenario               
        float radius=1.2f;                          //Es para setear el largo del escenario
        std::vector<RGBColor> pcolors={};           //Gama de colores
        //Objectos de referencia
        Engine* engine;
        //Metodos de creacion
        /*
            Reserva el siguiente espacio de atributos, como recomendacion se llama al final de cada insercion de valores
        */
        void reserveArgSpace(){
            argsused+=argspace.at(argpointer);
            argpointer++;
        }
        unsigned int calculateStride(){
            unsigned int argstride=0;
            for(int i=0; i<=argpointer; i++){
                argstride+=argspace.at(i);
            }
            return argstride;
        }
        void restartSpacing(){
            argsused=0;
            argpointer=0;
        }
        /*
            Añade un color a la mezcla de vertices
        */
        void pushColorRaw(RGBColor color){
            vertexs.push_back(color.R);
            vertexs.push_back(color.G);
            vertexs.push_back(color.B);
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
            Añade una coordenada 3D, en base a un vector de coordenadas determinado
        */
        void pushCoor3D(std::vector<Coor3D>&coors, Coor3D coor){
            coors.push_back(coor);
        }
        /*
            Añade una coordenada 3D y un color a la vez al conjunto de vértices
        */
        void pushCoor3DWRGB(Coor3D coor, RGBColor color){
            pushCoor3D(coor);
            pushColorRaw(color);
        }
        /*
            Añade una coordenada 3D a la mezcla de vertices, dependiendo del desplazamiento
        */
       void insertCoor3DAt(Coor3D coor, int offset){
        vertexs.insert(vertexs.begin()+offset, coor.x);
        vertexs.insert(vertexs.begin()+offset+1, coor.y);
        vertexs.insert(vertexs.begin()+offset+2, coor.z);
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
        void pushTriangle2(Coor3D A, Coor3D B, Coor3D C){
            pushCoor3D(allvcoors, A);
            pushCoor3D(allvcoors, B);
            pushCoor3D(allvcoors, C);
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
            //std::vector<Coor3D> tempv={};
            Coor3D currentcoor;
            currentcoor.x=0.0f;
            currentcoor.y=0.0f;
            currentcoor.z=0.0f;
            float anglex = (float)(4*acos(0.0)/vnumber);
            vcoors.push_back(currentcoor);
            for (int i=0; i<vnumber; i++){
                currentcoor.x=radius*cos(anglex*i);
                currentcoor.y=radius*sin(anglex*i);
                vcoors.push_back(currentcoor);
            }
            vertexs=createTriangles(vcoors);
            allvcoors=createTriangles2(vcoors);
            reserveArgSpace();
            return vertexs;
        }
        /*
            Guarda datos escenciales para el trazado del nuevo escenario (traza un poligono regular), con vertices puros
        */
        std::vector<Coor3D> setNewRegular(float radius, unsigned int vnumber){
            restartSpacing();
            std::vector<Coor3D> vcoorscopy=vcoors;
            vcoors.clear();
            Coor3D currentcoor;
            currentcoor.x=0.0f;
            currentcoor.y=0.0f;
            currentcoor.z=0.0f;
            float anglex = (float)(4*acos(0.0)/vnumber);
            vcoors.push_back(currentcoor);
            for (int i=0; i<vnumber; i++){
                currentcoor.x=radius*cos(anglex*i);
                currentcoor.y=radius*sin(anglex*i);
                vcoors.push_back(currentcoor);
            }
            if(this->vnumber>=vnumber){
                vertexs.clear();
                vertexs=createTriangles(vcoors);
                allvcoors.clear();
                allvcoorscopy=createTriangles2(vcoors);
                for(int i=0; i<(this->vnumber-vnumber); i++){
                    vcoors.push_back(vcoors.back());
                }
            }else{
                for(int i=0; i<(vnumber-this->vnumber); i++){
                    vcoorscopy.push_back(vcoorscopy.back());
                }
                vertexs.clear();
                vertexs=createTriangles(vcoorscopy);
            }
            allvcoors.clear();
            allvcoors=createTriangles2(vcoors);
            reserveArgSpace();
            return allvcoors;
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
        std::vector<Coor3D> createTriangles2(std::vector<Coor3D>coors){
            for(int i=1; i<(coors.size()-1); i++){
                pushTriangle2(coors.at(0), coors.at(i), coors.at(i+1));
            }
            pushTriangle2(coors.at(0), coors.at(coors.size()-1), coors.at(1));
            return allvcoors;
        }
        /*
            Inserta los colores en las coordenadas de las posiciones con algo de estilo
        */
        std::vector<float> addColors(unsigned int vnum, unsigned int timesto, std::vector<RGBColor>&colors){
            //std::cout << "Numero de vertices: " << vnum << std::endl;
            vertexcolors.clear();           //Limpio primero que nada
            int stride = calculateStride(); //Stride
            int checkin = 0;
            RGBColor newColor;
            for(int i=0; i<vnum-timesto; i++){
                //std::cout << "Insertando en index: " << (3 + i* offset) << std::endl;
                newColor = setColorPattern(checkin, timesto, colors);
                insertColorAt(newColor, argsused+i*stride);
                pushColor(vertexcolors, newColor);
                checkin++;
            }
            //Define el ultimo color si el poligono es par
            if((vnum/3)%2==0){
                for(int i=0;i<timesto;i++){
                    //std::cout << "Insertando en index: " << (3 +(vnum-timesto+i)* offset) << std::endl;
                    newColor = setColorPattern(checkin, timesto, colors);
                    insertColorAt(newColor, argsused+(vnum-timesto+i)*stride);
                    pushColor(vertexcolors, newColor);
                    checkin++;
                }
            }else{
                //pushColor(vertexcolors, colors.back());
                for(int i=0;i<timesto;i++){
                    //std::cout << "Insertando en index: " << (3 +(vnum-timesto+i)* offset) << std::endl;
                    newColor = colors.back();
                    insertColorAt(newColor, argsused+(vnum-timesto+i)*stride);
                    pushColor(vertexcolors, newColor);
                }
            }
            reserveArgSpace();          
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
        /*
            Rellena las coordenadas para al iniciar el objeto
        */
        std::vector<float> padCoors(unsigned int vnum, std::vector<Coor3D>&coors){
            int stride = calculateStride();
            for(int i=0; i<vnum; i++){
                //std::cout << "Insertando en index: " << (3 + i* stride) << std::endl;
                insertCoor3DAt(coors.at(i), argsused+i*stride);
            }
            reserveArgSpace();
            return vertexs;
        }
        /*
            Actualiza un atributo
        */
    public:
        //Constructors
        BG()=default;
        BG(Engine* engine, float radius, unsigned int vnum, unsigned int patterntimesto, std::vector<RGBColor>&colors, Type type):
            engine(engine)
        {
            std::cout<<"Oh me creooo, dice BG"<<std::endl;
            engine->initializeCustom(radius);
            this->radius=radius;
            pcolors = colors;
            vnumber = vnum;
            timesto = patterntimesto;
            if(type==Type::INDEXED){
                vertexs = setRegular(radius, vnum);
                indexes = createIndexes(vnum);
                //Memoria del objeto
                //IDs.push_back(engine->createBuffer3D(vertexs, &indexes, false).VAO);
                IDs.push_back(engine->createBuffer(vertexs, &indexes, 3, argspace));
            }else if (type==Type::CLASSIC){
                vertexs = rawsetRegular(radius, vnum);
                vertexs = addColors(vertexs.size()/3, timesto, colors);
                vertexs = padCoors(vertexs.size()/6, allvcoors);
                //Memoria del objeto
                //IDs.push_back(engine->createBuffer3D(vertexs, NULL, true).VAO);
                IDs.push_back(engine->createBuffer(vertexs, NULL, 9, argspace));
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
        /*
            Vista
        */
        void setPerspective(float FOV, float nearD, float farD){
            engine->setFOV(FOV);
            engine->setnearD(nearD);
            engine->setfarD(farD);
            engine->modifyPerspective(FOV, nearD, farD);
        }
        /*
            Vista
        */
        void setCamera(float x, float y, float z){
            engine->setupView(x, y, z);
        }
        /*
            Escala
        */
        void setScale(float factor){
            engine->setupscale3D(factor);
        }
        /*
            Renderizar/Mostrar
        */
        void show() {
            engine->renderPolygon2(this->getID(0), getVertexs().size());
        }
        /*
            Intercambia los colores de BG con los de su vecino
        */
        void swapColors(){
            std::rotate(vertexcolors.begin(), vertexcolors.begin()+timesto, vertexcolors.end());
            engine->updateBufferColorWeight(this->getID(0),vertexcolors,1,argspace);
        }
        /*
            Reserva la posicion para realizar el morphing
        */
        void prepareBGforDecrease(int sides){
            //Guardo nuevas coordenadas al buffer
            allvcoors=setNewRegular(radius, sides);
            engine->updateBufferCoorWeight(this->getID(0),allvcoors,2,argspace);
            //Preparo vertexs para temas de consistencia
            vertexs=addColors(vertexs.size()/3, timesto, pcolors);
            vertexs=padCoors(vertexs.size()/6, allvcoorscopy); //El error
            //Comentalo si quieres
            std::cout << "[ ";
            for (float val : vertexs) {
                std::cout << val << " ";
            }
            std::cout << "]" << std::endl;
        }
        void prepareBGforIncrease(int sides){
            //Preparo vertexs para temas de consistencia
            allvcoors=setNewRegular(radius, sides);
            vertexs=addColors(vertexs.size()/3, timesto, pcolors);
            vertexs=padCoors(vertexs.size()/6, allvcoors);
            this->vnumber=sides;
            engine->updateBuffer(this->getID(0),vertexs, NULL);
            //Comentalo si quieres
            std::cout << "[ ";
            for (float val : vertexs) {
                std::cout << val << " ";
            }
            std::cout << "]" << std::endl;
        }
        /*
            Cambia los lados de todo el escenario de manera cinematica (morphing)
        */
        void softchangeSides(float step){
            std::cout<<"Esta cambiando"<<std::endl;
            engine->polygonRadiusPolarMorph3D(radius, step);
        }
        /*
            Actualiza solo al terminar (morphing)
        */
        void endUpdate(float step){
            if(step==1.0f) engine->updateBuffer(this->getID(0),vertexs, NULL);
            std::cout<<"Cambio"<<std::endl;
        }
        /*
            Cambia el HUE del escenario
        */
        void changeBGHue(float time, float BGHueFactor, float BGHueSpeed){
            engine->changeHue(time, BGHueFactor, BGHueSpeed);
        }
        /*
            Rota el escenario
        */
        void rotateBG(float time, float RX, float RY, float RZ){
            engine->rotate3D(time, RX, RY, RZ);
        }
        /*
            Escala el escenario
        */
        void scaleBG(float factor){
            engine->scale3D(factor);
        }
};

#endif