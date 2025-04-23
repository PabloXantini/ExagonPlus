#ifndef CENTER_HPP
#define CENTER_HPP

#include "GEngine/Engine.hpp"
#include "GEngine/Shader.hpp"
#include "../resource.h"
#include "utils/Position.h"
#include "utils/Color.h"
#include "BG.hpp"

#include <iostream>
#include <vector>

class Center : public BG {
    private:
        std::vector<unsigned int> IDs={};           //Esto me permite saber que IDs tienen cada forma que vaya a renderizar
        std::vector<unsigned int> argspace={3,3,3}; //Pos//Color//toPos
        unsigned int argsused=0;
        unsigned int argpointer=0;

        std::vector<unsigned int> indexes={};       //Indices de generacion
        std::vector<float> vertexs={};              //Vertices brutos del objeto
        std::vector<float> wvertexs={};              //Vertices brutos del objeto

        //Borde
        std::vector<Coor3D> wvcoors={};             //Coordenadas 3D POR VERTICE (Origen)
        std::vector<Coor3D> wtovcoors={};           //Coordenadas 3D POR VERTICE (Destino)
        //Relleno
        std::vector<Coor3D> vcoors={};              //Coordenadas 3D POR VERTICE (Origen)
        std::vector<Coor3D> tovcoors={};            //Coordenadas 3D POR VERTICE (Destino)

        std::vector<RGBColor> vertexcolors={};      //Gama de colores POR VERTICE
        std::vector<RGBColor> wvertexcolors={};     //Colores de pared POR VERTICE
        //General
        unsigned int vnumber = 3;                   //Lados del centro
        unsigned int timesto = 6;                   //Veces en la que se reproducira el patron
        float radius=1.2f;                          //Es para setear el largo del centro
        float padding=0.1f;                         //Grosor del borde
        std::vector<RGBColor> pcolors;              //Color principal (por vertice)
        RGBColor wallcolor;                         //Color del contorno
        //Transformaciones
        glm::mat4 model = glm::mat4(1.0f);
        //Objetos de referencia
        Engine* engine;
        Shader* ShaderCenter;
        //Objetos usados
        //Metodos de creacion
        void initShaders(){
            ShaderCenter = ShaderBG;
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
            Añade un color a la mezcla de vertices, dependiendo del desplazamiento
        */
        void insertColorAt(std::vector<float>&vertexs, RGBColor color, int offset){
            vertexs.insert(vertexs.begin()+offset, color.R);
            vertexs.insert(vertexs.begin()+offset+1, color.G);
            vertexs.insert(vertexs.begin()+offset+2, color.B);
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
            Añade una coordenada 3D y un color a la vez al conjunto de vértices
        */
        void pushCoor3DWRGB(Coor3D coor, RGBColor color){
            PushCoor3D(coor);
            PushColor(color);
        }
        /*
            Añade una coordenada 3D a la mezcla de vertices, dependiendo del desplazamiento
        */
        void insertCoor3DAt(std::vector<float>&vertexs, Coor3D coor, int offset){
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
        void PushTriangle(Coor3D A, Coor3D B, Coor3D C){
            PushCoor3D(A);
            PushCoor3D(B);
            PushCoor3D(C);
        }
        /*
            Guarda datos escenciales para el trazado del escenario (traza un poligono regular), usando indices
        */
        std::vector<float> setRegular(std::vector<float>& vertexs, std::vector<Coor3D>& verts, float radius, unsigned int vnumber){
            restartSpacing();
            vertexs.clear();
            Coor3D currentcoor;
            currentcoor.x=0.0f;
            currentcoor.y=0.0f;
            currentcoor.z=0.0f;
            float anglex = (float)(4*acos(0.0)/vnumber);
            pushCoor3D(vertexs, currentcoor);
            verts.push_back(currentcoor);
            for (int i=0; i<vnumber; i++){
                currentcoor.x=radius*cos(anglex*i);
                currentcoor.y=radius*sin(anglex*i);
                pushCoor3D(vertexs, currentcoor);
                verts.push_back(currentcoor);
            }
            reserveArgSpace();
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
        std::vector<float> createTriangles(std::vector<Coor3D>coors){
            for(int i=1; i<(coors.size()-1); i++){
                PushTriangle(coors.at(0), coors.at(i), coors.at(i+1));
            }
            PushTriangle(coors.at(0), coors.at(coors.size()-1), coors.at(1));
            return vertexs;
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
            reserveArgSpace();
            return vertexs;
        }
        /*
            Guarda datos escenciales para el trazado del nuevo escenario (traza un poligono regular), con vertices puros
        */
        std::vector<Coor3D> setNewRegular(std::vector<float>& vertexs, std::vector<Coor3D>& verts, std::vector<Coor3D>& toverts, float radius, unsigned int vnumber){
            restartSpacing();
            std::vector<Coor3D> cvcoors=verts;         //Guarda las coordenadas anteriores
            //Reinicia las coordenadas
            verts.clear();
            toverts.clear();
            //Logica sacada otra vez para formar el nuevo poligono
            Coor3D currentcoor;
            currentcoor.x=0.0f;
            currentcoor.y=0.0f;
            currentcoor.z=0.0f;
            float anglex = (float)(4*acos(0.0)/vnumber);
            verts.push_back(currentcoor);
            toverts.push_back(currentcoor);
            for (int i=0; i<vnumber; i++){
                currentcoor.x=radius*cos(anglex*i);
                currentcoor.y=radius*sin(anglex*i);
                verts.push_back(currentcoor);
                toverts.push_back(currentcoor);
            }
            //Evalua los casos en los que debe reducir el numero de poligonos
            if(this->vnumber>=vnumber){                 //Decrease
                for(int i=0; i<(this->vnumber-vnumber); i++){
                    toverts.push_back(toverts.back());
                }
                //Prepara las coordenadas
                vertexs.clear();
                for(auto& coor : verts){
                    pushCoor3D(vertexs, coor);
                }
                //allvcoors.clear();
                //toallvcoors.clear();

                //allvcoors=BG::createTriangles(allvcoors, cvcoors);      //Pre Atrib 0
                //toallvcoors=BG::createTriangles(toallvcoors, tovcoors); //Pre Atrib 2
                //vertexs=createTriangles(vcoors);                        //Pos Atrib 0              
            }else{                                      //Increase
                for(int i=0; i<(vnumber-this->vnumber); i++){
                    cvcoors.push_back(cvcoors.back());
                }
                vertexs.clear();
                for(auto& coor : cvcoors){
                    pushCoor3D(vertexs, coor);
                }
                //allvcoors.clear();
                //toallvcoors.clear();

                //vertexs=createTriangles(cvcoors);                       //Pre Atrib 0
                //toallvcoors=BG::createTriangles(toallvcoors, tovcoors); //Pre Atrib 2
                //allvcoors=BG::createTriangles(allvcoors, vcoors);       //Pos Atrib 2             
            }
            reserveArgSpace();
            return toverts;
        }
        /*
            Crea los triangulos de manera bruta para la manera CLASSIC
        */
        std::vector<float> createTriangles(std::vector<float>&vertexs, std::vector<Coor3D>coors){
            for(int i=1; i<(coors.size()-1); i++){
                PushTriangle(coors.at(0), coors.at(i), coors.at(i+1));
            }
            PushTriangle(coors.at(0), coors.at(coors.size()-1), coors.at(1));
            return vertexs;
        }
        /*
            Inserta los colores en las coordenadas de las posiciones con algo de estilo
        */
        std::vector<float> addColors(std::vector<float>&vertexs, unsigned int vnum, unsigned int timesto, std::vector<RGBColor>&colors){
            //std::cout << "Numero de vertices: " << vnum << std::endl;
            vertexcolors.clear();           //Limpio primero que nada
            int stride = calculateStride(); //Stride
            int checkin = 0;
            RGBColor newColor;
            for(int i=0; i<vnum; i++){
                //std::cout << "Insertando en index: " << (3 + i* offset) << std::endl;
                newColor = setColorPattern(checkin, timesto, colors);
                insertColorAt(vertexs, newColor, argsused+i*stride);
                pushColor(vertexcolors, newColor);
                checkin++;
            }
            reserveArgSpace();          
            return vertexs;
        }
        std::vector<float> addWallColor(std::vector<float>&vertexs, unsigned int vnum, RGBColor color){
            //std::cout << "Numero de vertices: " << vnum << std::endl;
            wvertexcolors.clear();           //Limpio primero que nada
            int stride = calculateStride(); //Stride
            for(int i=0; i<vnum; i++){
                //std::cout << "Insertando en index: " << (3 + i* offset) << std::endl;
                insertColorAt(vertexs, color, argsused+i*stride);
                pushColor(wvertexcolors, color);
            }
            reserveArgSpace();          
            return vertexs;
        }   
        /*
            Rellena las coordenadas para al iniciar el objeto
        */
        std::vector<float> padCoors(std::vector<float>&vertexs, unsigned int vnum, std::vector<Coor3D>&coors){
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
            int index = (check / timesto) % colors.size();
            RGBColor currentColor = colors.at(index);
        return currentColor;
    }
    public:
        //Constructors
        Center()=default;
        Center(Engine* engine, float radius, float padding,unsigned int vnum, unsigned int patterntimesto, std::vector<RGBColor>&colors, RGBColor bordercolor):
            engine(engine)
        {
            std::cout<<"Oh me creooo, dice Center"<<std::endl;
            initShaders();
            this->radius=radius;
            this->padding=padding;
            float cradius=radius-padding;
            timesto=patterntimesto;
            pcolors=colors;
            wallcolor=bordercolor;
            vnumber=vnum;
            indexes=createIndexes(vnum);
            //Contorno
            wvertexs=setRegular(wvertexs,wvcoors,radius,vnum);
            wvertexs=addWallColor(wvertexs,wvertexs.size()/3, bordercolor);
            wvertexs=padCoors(wvertexs,wvertexs.size()/6,wvcoors);
            //Relleno
            vertexs=setRegular(vertexs,vcoors,cradius,vnum);
            vertexs=addColors(vertexs,vertexs.size()/3, timesto, colors);
            vertexs=padCoors(vertexs,vertexs.size()/6,vcoors);
            //Memoria del objeto
            IDs.push_back(engine->createBuffer(wvertexs,&indexes,9,argspace));
            IDs.push_back(engine->createBuffer(vertexs,&indexes,9,argspace));
            //Comentalo si quieres
            std::cout << "[ ";
            for (float val : vertexs) {
                std::cout << val << " ";
            }
            std::cout << "]" << std::endl;
            std::cout << "[ ";
            for (float val : wvertexs) {
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
        /*
            Renderizar/Mostrar
        */
        void show() {
            ShaderBG->setMat4("Model", model);
            engine->renderPolygon(ShaderBG, this->getID(0), indexes.size());
            engine->renderPolygon(ShaderBG, this->getID(1), indexes.size());
        }
        /*
            Intercambia los colores de Center con los de su vecino
        */
        void swapColors(){
            std::rotate(vertexcolors.begin(), vertexcolors.begin()+timesto, vertexcolors.end());
            engine->updateBufferColorWeight(this->getID(1),vertexcolors,1,argspace);
        }
        /*
            Reserva la posicion para realizar el morphing
        */
        void prepareCenterforDecrease(int sides){         
            //Valor temporal
            std::vector<Coor3D> wvcoorscopy = wvcoors;
            std::vector<Coor3D> vcoorscopy = vcoors;
            //Guardo nuevas coordenadas al buffer
            //Pared
            wtovcoors=setNewRegular(wvertexs, wvcoors, wtovcoors, radius, sides);
            engine->updateBufferCoorWeight(this->getID(0),wvcoorscopy,0,argspace);
            engine->updateBufferCoorWeight(this->getID(0),wtovcoors,2,argspace);
            //Preparo vertexs para temas de consistencia
            wvertexs=addWallColor(wvertexs, wvertexs.size()/3, wallcolor);
            wvertexs=padCoors(wvertexs, wvertexs.size()/6, wtovcoors);
            //Relleno
            float cradius=radius-padding;
            tovcoors=setNewRegular(vertexs, vcoors, tovcoors, cradius, sides);
            engine->updateBufferCoorWeight(this->getID(1),vcoorscopy,0,argspace);
            engine->updateBufferCoorWeight(this->getID(1),tovcoors,2,argspace);
            //Preparo vertexs para temas de consistencia
            vertexs=addColors(vertexs, vertexs.size()/3, timesto, pcolors);
            vertexs=padCoors(vertexs, vertexs.size()/6, tovcoors);
        }
        void prepareCenterforIncrease(int sides){
            //Preparo vertexs para temas de consistencia
            //Pared
            wtovcoors=setNewRegular(wvertexs, wvcoors, wtovcoors, radius, sides);
            wvertexs=addWallColor(wvertexs, wvertexs.size()/3, wallcolor);
            wvertexs=padCoors(wvertexs, wvertexs.size()/6, wtovcoors);
            //Relleno
            timesto=sides+1;
            float cradius=radius-padding;
            tovcoors=setNewRegular(vertexs, vcoors, tovcoors, cradius, sides);
            vertexs=addColors(vertexs, vertexs.size()/3, timesto, pcolors);
            vertexs=padCoors(vertexs, vertexs.size()/6, tovcoors);
            //Creo nuevos indices
            this->vnumber=sides;
            indexes=createIndexes(sides);
            engine->updateBuffer(this->getID(0),wvertexs, &indexes);
            engine->updateBuffer(this->getID(1),vertexs, &indexes);
        }
        /*
            Actualiza solo al terminar (morphing)
        */
        void endUpdate(int sides){
            //Creo nuevos indices
            this->vnumber=sides;
            timesto=sides+1;
            indexes=createIndexes(sides);
            engine->updateBuffer(this->getID(0),wvertexs, &indexes);
            engine->updateBuffer(this->getID(1),vertexs, &indexes);
        }
};

#endif