#ifndef BG_HPP
#define BG_HPP

#include "GEngine/Engine.hpp"
#include "GEngine/Shader.hpp"
#include "../resource.h"
#include "utils/Color.h"
#include "utils/Position.h"

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
        
        std::vector<Coor3D> vcoors={};              //Coordenadas 3D POR VERTICE (Origen)
        std::vector<Coor3D> tovcoors={};            //Coordenadas 3D POR VERTICE (Destino)
        std::vector<Coor3D> allvcoors={};           //Coordenadas 3D POR VERTICE - Triangulos (Origen)
        std::vector<Coor3D> toallvcoors={};         //Coordenadas 3D POR VERTICE - Triangulos (Destino)

        std::vector<RGBColor> vertexcolors={};      //Gama de colores POR VERTICE
        //General
        std::vector<float> skvertexs={};            //Coordenadas generales (Util para heredar)
        unsigned int timesto = 3;                   //Veces en la que se reproducir el patron
        unsigned int vnumber = 3;                   //Lados del escenario               
        float radius=1.2f;                          //Es para setear el largo del escenario
        std::vector<RGBColor> pcolors={};           //Gama de colores
        //Transformaciones
        glm::mat4 model = glm::mat4(1.0f);
        //Objectos de referencia
        Engine* engine;
        //Metodos de creacion
        /*
            Inicializacion de Shader
        */
        void initShaders(){
            ShaderBG = new Shader(IDR_VSHADER2,IDR_FSHADER2);
            //Registro
            engine->registerShader(ShaderBG);
            //Inicializacion
            ShaderBG->setFloat("morphprogress",0.0f);
        }
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
        void PushColor(RGBColor color){
            vertexs.push_back(color.R);
            vertexs.push_back(color.G);
            vertexs.push_back(color.B);
        }
        /*
            Añade una coordenada 3D
        */
        void PushCoor3D(Coor3D coors){
            vertexs.push_back(coors.x);
            vertexs.push_back(coors.y);
            vertexs.push_back(coors.z);
        }
        /*
            Inserta un triangulo al conjunto de indices
        */
        void pushVTriangle(unsigned int a, unsigned int b, unsigned int c){
            indexes.push_back(a);
            indexes.push_back(b);
            indexes.push_back(c);
        }
        /*
            Inserta un triangulo indicado por las coordenadas del triangulo
        */
        void PushTriangle(Coor3D A, Coor3D B, Coor3D C){
            PushCoor3D(A);
            PushCoor3D(B);
            PushCoor3D(C);
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
            PushCoor3D(currentcoor);
            for (int i=0; i<vnumber; i++){
                currentcoor.x=radius*cos(anglex*i);
                currentcoor.y=radius*sin(anglex*i);
                PushCoor3D(currentcoor); 
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
            tovcoors=vcoors;                       //Guardo para despues
            vertexs=createTriangles(vcoors);
            allvcoors=createTriangles(allvcoors, vcoors);
            reserveArgSpace();
            return vertexs;
        }
        /*
            Guarda datos escenciales para el trazado del nuevo escenario (traza un poligono regular), con vertices puros
        */
        std::vector<Coor3D> setNewRegular(float radius, unsigned int vnumber){
            restartSpacing();
            std::vector<Coor3D> cvcoors=vcoors;         //Guarda las coordenadas anteriores
            //Reinicia las coordenadas
            vcoors.clear();
            tovcoors.clear();
            //Logica sacada otra vez para formar el nuevo poligono
            Coor3D currentcoor;
            currentcoor.x=0.0f;
            currentcoor.y=0.0f;
            currentcoor.z=0.0f;
            float anglex = (float)(4*acos(0.0)/vnumber);
            vcoors.push_back(currentcoor);
            tovcoors.push_back(currentcoor);
            for (int i=0; i<vnumber; i++){
                currentcoor.x=radius*cos(anglex*i);
                currentcoor.y=radius*sin(anglex*i);
                vcoors.push_back(currentcoor);
                tovcoors.push_back(currentcoor);
            }
            //Evalua los casos en los que debe reducir el numero de poligonos
            if(this->vnumber>=vnumber){                 //Decrease
                for(int i=0; i<(this->vnumber-vnumber); i++){
                    tovcoors.push_back(tovcoors.back());
                }
                //Prepara las coordenadas
                vertexs.clear();
                allvcoors.clear();
                toallvcoors.clear();

                allvcoors=createTriangles(allvcoors, cvcoors);      //Pre Atrib 0
                toallvcoors=createTriangles(toallvcoors, tovcoors); //Pre Atrib 2
                vertexs=createTriangles(vcoors);                    //Pos Atrib 0              
            }else{                                      //Increase
                for(int i=0; i<(vnumber-this->vnumber); i++){
                    cvcoors.push_back(cvcoors.back());
                }
                vertexs.clear();
                allvcoors.clear();
                toallvcoors.clear();

                vertexs=createTriangles(cvcoors);                   //Pre Atrib 0
                toallvcoors=createTriangles(toallvcoors, tovcoors); //Pre Atrib 2
                allvcoors=createTriangles(allvcoors, vcoors);       //Pos Atrib 2             
            }
            reserveArgSpace();
            return toallvcoors;
        }
        /*
            Crea los triangulos de manera bruta para la manera CLASSIC
        */
        std::vector<float> createTriangles(std::vector<Coor3D>coors){
            for(int i=1; i<(coors.size()-1); i++){
                PushTriangle(coors.at(0), coors.at(i), coors.at(i+1));
            }
            PushTriangle(coors.at(0), coors.at(coors.size()-1), coors.at(1));
            return vertexs;
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
                insertColorAt(vertexs, newColor, argsused+i*stride);
                pushColor(vertexcolors, newColor);
                checkin++;
            }
            //Define el ultimo color si el poligono es par
            if((vnum/3)%2==0){
                for(int i=0;i<timesto;i++){
                    //std::cout << "Insertando en index: " << (3 +(vnum-timesto+i)* offset) << std::endl;
                    newColor = setColorPattern(checkin, timesto, colors);
                    insertColorAt(vertexs, newColor, argsused+(vnum-timesto+i)*stride);
                    pushColor(vertexcolors, newColor);
                    checkin++;
                }
            }else{
                //pushColor(vertexcolors, colors.back());
                for(int i=0;i<timesto;i++){
                    //std::cout << "Insertando en index: " << (3 +(vnum-timesto+i)* offset) << std::endl;
                    newColor = colors.back();
                    insertColorAt(vertexs, newColor, argsused+(vnum-timesto+i)*stride);
                    pushColor(vertexcolors, newColor);
                }
            }
            reserveArgSpace();          
            return vertexs;
        }
        /*
            Rellena las coordenadas para al iniciar el objeto
        */
        std::vector<float> padCoors(unsigned int vnum, std::vector<Coor3D>&coors){
            int stride = calculateStride();
            for(int i=0; i<vnum; i++){
                //std::cout << "Insertando en index: " << (3 + i* stride) << std::endl;
                insertCoor3DAt(vertexs, coors.at(i), argsused+i*stride);
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
    protected:
        //Variables compartidas
        Shader* ShaderBG;
        //Metodos compartidos
        /*
            Crea los triangulos de manera bruta para la manera CLASSIC usando coordenadas
        */
        std::vector<Coor3D> createTriangles(std::vector<Coor3D>&vcoors, std::vector<Coor3D>coors){
            for(int i=1; i<(coors.size()-1); i++){
                pushTriangle(vcoors, coors.at(0), coors.at(i), coors.at(i+1));
            }
            pushTriangle(vcoors, coors.at(0), coors.at(coors.size()-1), coors.at(1));
            return vcoors;
        }
    public:
        //Constructors
        BG()=default;
        BG(Engine* engine, float radius, unsigned int vnum, unsigned int patterntimesto, std::vector<RGBColor>&colors, Type type):
            engine(engine)
        {
            std::cout<<"Oh me creooo, dice BG"<<std::endl;
            //engine->initializeCustom();
            initShaders();
            this->radius=radius;
            pcolors = colors;
            vnumber = vnum;
            timesto = patterntimesto;
            if(type==Type::INDEXED){
                vertexs = setRegular(radius, vnum);
                indexes = createIndexes(vnum);
                //Memoria del objeto
                IDs.push_back(engine->createBuffer(vertexs, &indexes, 3, argspace));
            }else if (type==Type::CLASSIC){
                vertexs = rawsetRegular(radius, vnum);
                vertexs = addColors(vertexs.size()/3, timesto, colors);
                vertexs = padCoors(vertexs.size()/6, allvcoors);
                //Memoria del objeto
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
            engine->setViewAll(x, y, z);
        }
        /*
            Renderizar/Mostrar
        */
        void show() {
            ShaderBG->setMat4("Model", model);
            engine->renderPolygon2(ShaderBG, this->getID(0), getVertexs().size());
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
            toallvcoors=setNewRegular(radius, sides);
            engine->updateBufferCoorWeight(this->getID(0),allvcoors,0,argspace);
            engine->updateBufferCoorWeight(this->getID(0),toallvcoors,2,argspace);
            //Preparo vertexs para temas de consistencia
            allvcoors.clear();
            allvcoors=createTriangles(allvcoors, vcoors);
            vertexs=addColors(vertexs.size()/3, timesto, pcolors);
            vertexs=padCoors(vertexs.size()/6, allvcoors);
            //Comentalo si quieres
            /*
            std::cout << "[ ";
            for (float val : vertexs) {
                std::cout << val << " ";
            }
            std::cout << "]" << std::endl;
            */
        }
        void prepareBGforIncrease(int sides){
            //Preparo vertexs para temas de consistencia
            toallvcoors=setNewRegular(radius, sides);
            vertexs=addColors(vertexs.size()/3, timesto, pcolors);
            vertexs=padCoors(vertexs.size()/6, toallvcoors);
            this->vnumber=sides;
            engine->updateBuffer(this->getID(0),vertexs, NULL);
            //Comentalo si quieres
            /*
            std::cout << "[ ";
            for (float val : vertexs) {
                std::cout << val << " ";
            }
            std::cout << "]" << std::endl;
            */
        }
        /*
            Cambia los lados de todo el escenario de manera cinematica (morphing)
        */
        void softchangeSides(float step){
            //std::cout<<"Esta cambiando"<<std::endl;
            ShaderBG->setFloat("morphprogress",step);
        }
        /*
            Actualiza solo al terminar (morphing)
        */
        void endUpdate(int sides){
            this->vnumber=sides;
            engine->updateBuffer(this->getID(0),vertexs, NULL);
            //std::cout<<"Cambio"<<std::endl;
        }
        /*
            Cambia el HUE del escenario
        */
        void changeBGHue(float time, float BGHueFactor, float BGHueSpeed){
            ShaderBG->setFloat("uTime",time);
            ShaderBG->setFloat("HueFactor",BGHueFactor);
            ShaderBG->setFloat("HueSpeed",BGHueSpeed);
        }
        /*
            Rota el escenario
        */
        void rotateBG(float time, float RX, float RY, float RZ){
            glm::mat4 rot = glm::mat4(1.0);
            rot = glm::rotate(rot, glm::radians(time*RX), glm::vec3(1.0,0.0,0.0)); //Rotation en el eje X
            rot = glm::rotate(rot, glm::radians(time*RY), glm::vec3(0.0,1.0,0.0)); //Rotation en el eje Y
            rot = glm::rotate(rot, glm::radians(time*RZ), glm::vec3(0.0,0.0,1.0)); //Rotation en el eje Z
            ShaderBG->setMat4("Rotation",rot);
        }
};

#endif