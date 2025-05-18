#ifndef BG_HPP
#define BG_HPP

#include "GEngine/Engine.hpp"
#include "GEngine/Shader.hpp"
#include "utils/Vertex.h"
#include "utils/Color.h"
#include "utils/Position.h"

#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>

class BG{
    private:
        //Variables propias de la clase
        //Graficos
        std::vector<unsigned int> IDs={};               //Esto me permite saber que IDs tienen cada forma que vaya a renderizar
        std::vector<unsigned int> argspace={3,3,3,3};   //Pos//Color//toPos//toColor
        unsigned int argsused=0;
        unsigned int argpointer=0;

        std::vector<unsigned int> indexes={};           //Indices de generacion
        std::vector<WVertex3D> vertexs={};              //Vertices brutos del objeto
        
        std::vector<Coor3D> vcoors={};                  //Coordenadas 3D POR VERTICE (Origen)
        std::vector<Coor3D> tovcoors={};                //Coordenadas 3D POR VERTICE (Destino)
        std::vector<Coor3D> allvcoors={};               //Coordenadas 3D POR VERTICE - Triangulos (Origen)
        std::vector<Coor3D> toallvcoors={};             //Coordenadas 3D POR VERTICE - Triangulos (Destino)

        std::vector<RGBColor> vertexcolors={};          //Gama de colores POR VERTICE
        //General
        std::vector<float> skvertexs={};                //Coordenadas generales (Util para heredar)
        unsigned int timesto = 3;                       //Veces en la que se reproducir el patron
        unsigned int vnumber = 3;                       //Lados del escenario               
        float radius=1.2f;                              //Es para setear el largo del escenario
        std::vector<RGBColor> pcolors={};               //Gama de colores
        //Transformaciones
        float BGRotX=0.0f;
        float BGRotY=0.0f;
        float BGRotZ=0.0f;
        glm::mat4 model = glm::mat4(1.0f);
        //Objectos de referencia
        Engine* engine;
        //Metodos de creacion
        /*
            Inicializacion de Shader
        */
        void initShaders(){
            //Registro
            engine->registerShader(ShaderBG);
            //Inicializacion
            ShaderBG->setFloat("morphprogress",0.0f);
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
            Crea los indices, con lo que se va trazar cada triangulo de manera INDEXED
        */
        std::vector<unsigned int> createIndexes(unsigned int vnumber){
            indexes.clear();
            for(unsigned int i=1; i<vnumber; i++){
                pushVTriangle(0, i, i+1);
            }
            pushVTriangle(0, vnumber, 1);
            return indexes;
        }
        /*
            Guarda datos escenciales para el trazado del escenario (traza un poligono regular), con vertices puros
        */
        std::vector<Coor3D> setRegular(float radius, unsigned int vnumber){
            vcoors.clear();
            //std::vector<Coor3D> tempv={};
            Coor3D currentcoor;
            currentcoor.x=0.0f;
            currentcoor.y=0.0f;
            currentcoor.z=0.0f;
            float anglex = (float)(4*acos(0.0)/vnumber);
            vcoors.push_back(currentcoor);
            for (unsigned int i=0; i<vnumber; i++){
                currentcoor.x=radius*cos(anglex*i);
                currentcoor.y=radius*sin(anglex*i);
                vcoors.push_back(currentcoor);
            }
            tovcoors=vcoors;                       //Guardo para despues
            allvcoors=createTriangles(allvcoors, vcoors);
            //reserveArgSpace();
            return vcoors;
        }
        /*
            Guarda datos escenciales para el trazado del nuevo escenario (traza un poligono regular), con vertices puros
        */
        std::vector<Coor3D> setNewRegular(float radius, unsigned int vnumber){
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
            for (unsigned int i=0; i<vnumber; i++){
                currentcoor.x=radius*cos(anglex*i);
                currentcoor.y=radius*sin(anglex*i);
                vcoors.push_back(currentcoor);
                tovcoors.push_back(currentcoor);
            }
            //Evalua los casos en los que debe reducir el numero de poligonos
            if(this->vnumber>=vnumber){                 //Decrease
                for(unsigned int i=0; i<(this->vnumber-vnumber); i++){
                    tovcoors.push_back(tovcoors.back());
                }
                //Prepara las coordenadas
                //vertexs.clear();                                  //Limpio antes que nada
                allvcoors.clear();
                toallvcoors.clear();
                
                allvcoors=createTriangles(allvcoors, cvcoors);      //Pre Atrib 0
                toallvcoors=createTriangles(toallvcoors, tovcoors); //Pre Atrib 2
                //vcoors                                            //Pos Atrib 0              
            }else{                                      //Increase
                for(unsigned int i=0; i<(vnumber-this->vnumber); i++){
                    cvcoors.push_back(cvcoors.back());
                }
                //vertexs.clear();                                   //Limpio antes que nada
                allvcoors.clear();
                toallvcoors.clear();
            
                //cvcoors                                           //Pre Atrib 0
                toallvcoors=createTriangles(toallvcoors, tovcoors); //Pre Atrib 2
                allvcoors=createTriangles(allvcoors, cvcoors);      //Pos Atrib 2             
            }
            return toallvcoors;
        }
        void addColors(unsigned int vnum, unsigned int timesto, std::vector<RGBColor>&colors){
            //std::cout << "Numero de vertices: " << vnum << std::endl;
            vertexcolors.clear();           //Limpio primero que nada
            int checkin = 0;
            RGBColor newColor;
            for(unsigned int i=0; i<vnum-timesto; i++){
                newColor = setColorPattern(checkin, timesto, colors);
                pushColor(vertexcolors, newColor);
                checkin++;
            }
            //Define el ultimo color si el poligono es par
            if((vnum/3)%2==0){
                for(unsigned int i=0;i<timesto;i++){
                    newColor = setColorPattern(checkin, timesto, colors);
                    pushColor(vertexcolors, newColor);
                    checkin++;
                }
            }else{
                for(unsigned int i=0;i<timesto;i++){
                    newColor = colors.back();
                    pushColor(vertexcolors, newColor);
                }
            }        
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
            for(unsigned int i=1; i<(coors.size()-1); i++){
                pushTriangle(vcoors, coors.at(0), coors.at(i), coors.at(i+1));
            }
            pushTriangle(vcoors, coors.at(0), coors.at(coors.size()-1), coors.at(1));
            return vcoors;
        }
        /*
            Sirve para inicializar la malla de vertices
        */
        std::vector<WVertex3D> setupMesh(std::vector<Coor3D>&vcoors, std::vector<RGBColor>&colors, std::vector<Coor3D>&tovcoors, std::vector<RGBColor>&tocolors){
            std::vector<WVertex3D> vertexs;
            for(unsigned int i=0; i<vcoors.size(); i++){
                pushWVertex(vertexs, vcoors.at(i), colors.at(i), tovcoors.at(i), tocolors.at(i));
            }
            return vertexs;
        }
        /*
            Sirve para sobrescribir valores dentro de la malla de vertices
        */
        std::vector<WVertex3D> modMesh(std::vector<WVertex3D>& vertexs, const std::vector<Coor3D>* vertcoors, const std::vector<RGBColor>* colors, const std::vector<Coor3D>* tovertcoors, const std::vector<RGBColor>* tocolors){
            for(unsigned int i=0; i<vertexs.size(); i++){
                if(vertcoors) putPosition(vertexs.at(i), vertcoors->at(i));
                if(colors) putColor(vertexs.at(i), colors->at(i));
                if(tovertcoors) putToPosition(vertexs.at(i), tovertcoors->at(i));
                if(tocolors) putToColor(vertexs.at(i), tocolors->at(i));
            }
            return vertexs;
        }
        /*
            Normaliza un angulo de rotacion
        */
        float normalizeAngle(float angle){
            angle=std::fmod(angle,360.0f);
            if(angle<0.0f) angle+=360.0f;
            return angle; 
        }
        /*
            Obtiene un vector de rotacion
        */
        glm::vec3 getRotVector(float rotation){
            return glm::normalize(glm::vec3(std::cos(glm::radians(rotation)),std::sin(glm::radians(rotation)),0.0f));
        }
    public:
        //Constructors
        BG()=default;
        BG(Engine* engine, Shader* shader, float radius, unsigned int vnum, unsigned int patterntimesto, std::vector<RGBColor>&colors):
            engine(engine),
            ShaderBG(shader)
        {
            std::cout<<"Oh me creooo, dice BG"<<std::endl;
            initShaders();
            this->radius=radius;
            pcolors = colors;
            vnumber = vnum;
            timesto = patterntimesto;
            //Background
            setRegular(radius,vnum);
            addColors(allvcoors.size(), timesto, colors);
            vertexs = setupMesh(allvcoors, vertexcolors, allvcoors, vertexcolors);
            //Memoria del objeto
            IDs.push_back(engine->createBuffer(vertexs, NULL, 12, argspace));
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
        const unsigned int getVertexCount() const {
            unsigned int vnum = vnumber+1;
            return vnum;
        }
        const std::vector<RGBColor>&getColors() const {
            return pcolors;
        }
        //Setters
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
            ShaderBG->setInt("ObjectType", 0);
            ShaderBG->setMat4("Model", model);
            engine->renderPolygon2(ShaderBG, this->getID(0), getVertexs().size()*12);
        }
        /*
            Intercambia los colores de BG con los de su vecino
        */
        void swapColors(){
            std::rotate(vertexcolors.begin(), vertexcolors.begin()+timesto, vertexcolors.end());
            vertexs = modMesh(vertexs, NULL, &vertexcolors, NULL, &vertexcolors);
            engine->modBuffer(this->getID(0),vertexs,NULL);
        }
        /*
            Reserva la posicion para realizar el morphing
        */
        void prepareBGforDecrease(int sides){
            //Guardo nuevas coordenadas al buffer
            toallvcoors=setNewRegular(radius, sides);
            vertexs=modMesh(vertexs, &allvcoors, NULL, &toallvcoors, NULL);
            engine->modBuffer(this->getID(0),vertexs, NULL);
            //Preparo vertexs para temas de consistencia
            allvcoors.clear();
            createTriangles(allvcoors, vcoors);
            addColors(allvcoors.size(), timesto, pcolors);
            vertexs=setupMesh(allvcoors, vertexcolors, allvcoors, vertexcolors);
        }
        void prepareBGforIncrease(int sides){
            //Preparo vertexs para temas de consistencia
            toallvcoors=setNewRegular(radius, sides);
            addColors(allvcoors.size(), timesto, pcolors);
            vertexs=setupMesh(allvcoors, vertexcolors, toallvcoors, vertexcolors);
            this->vnumber=sides;
            engine->updateBuffer(this->getID(0),vertexs, NULL);
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
        void rotateBG(float step, float RX, float RY, float RZ){
            glm::mat4 rot = glm::mat4(1.0);
            BGRotX+=step*RX;
            BGRotY+=step*RY;
            BGRotZ+=step*RZ;
            rot = glm::rotate(rot, glm::radians(BGRotX), glm::vec3(1.0,0.0,0.0)); //Rotation en el eje X
            rot = glm::rotate(rot, glm::radians(BGRotY), glm::vec3(0.0,1.0,0.0)); //Rotation en el eje Y
            rot = glm::rotate(rot, glm::radians(BGRotZ), glm::vec3(0.0,0.0,1.0)); //Rotation en el eje Z
            ShaderBG->setMat4("Rotation",rot);
        }
        /*
            Reinicia las transformaciones
        */
        void restart(){
            glm::mat4 rot = glm::mat4(1.0);
            BGRotX=0.0f;
            BGRotY=0.0f;
            BGRotZ=0.0f;
            ShaderBG->setMat4("Rotation",rot);
        }
        /*
            Libera memoria de GPU
        */
        void free(){
            engine->eliminateBuffer(this->getID(0));
        }
};

#endif