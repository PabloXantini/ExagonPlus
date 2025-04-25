#ifndef CENTER_HPP
#define CENTER_HPP

#include "GEngine/Engine.hpp"
#include "GEngine/Shader.hpp"
#include "utils/Vertex.h"
#include "utils/Position.h"
#include "utils/Color.h"
#include "BG.hpp"

#include <iostream>
#include <vector>

class Center : public BG {
    protected:
        //Borde
        std::vector<Coor3D> wvcoors={};                 //Coordenadas 3D POR VERTICE (Origen)
        std::vector<Coor3D> wtovcoors={};               //Coordenadas 3D POR VERTICE (Destino)
        unsigned int vnumber = 3;                       //Lados del centro
    private:
        std::vector<unsigned int> IDs={};               //Esto me permite saber que IDs tienen cada forma que vaya a renderizar
        std::vector<unsigned int> argspace={3,3,3,3};   //Pos//Color//toPos//toColor
        unsigned int argsused=0;
        unsigned int argpointer=0;

        std::vector<unsigned int> indexes={};           //Indices de generacion
        std::vector<WVertex3D> vertexs={};              //Vertices brutos del objeto
        std::vector<WVertex3D> wvertexs={};             //Vertices brutos del objeto
        //std::vector<float> vertexs={};                  //Vertices brutos del objeto
        //std::vector<float> wvertexs={};                 //Vertices brutos del objeto
        //Relleno
        std::vector<Coor3D> vcoors={};                  //Coordenadas 3D POR VERTICE (Origen)
        std::vector<Coor3D> tovcoors={};                //Coordenadas 3D POR VERTICE (Destino)
        std::vector<Coor3D> tempcoors={};               //Coordenadas 3D POR VERTICES (Para descargar memoria)

        std::vector<RGBColor> vertexcolors={};          //Gama de colores POR VERTICE
        std::vector<RGBColor> wvertexcolors={};         //Colores de pared POR VERTICE
        //General
        unsigned int timesto = 6;                       //Veces en la que se reproducira el patron
        float radius=1.2f;                              //Es para setear el largo del centro
        float padding=0.1f;                             //Grosor del borde
        std::vector<RGBColor> pcolors;                  //Color principal (por vertice)
        RGBColor wallcolor;                             //Color del contorno
        //Transformaciones
        glm::mat4 model = glm::mat4(1.0f);
        //Objetos de referencia
        Engine* engine;
        Shader* ShaderCenter;
        //Objetos usados
        //Metodos de creacion
        void initShaders(){
            //ShaderCenter = ShaderBG;
            //std::cout << "ShaderCenter ptr: " << ShaderCenter << std::endl;
            //engine->registerShader(ShaderCenter);
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

        void PushColor(RGBColor color){
            vertexs.push_back(color.R);
            vertexs.push_back(color.G);
            vertexs.push_back(color.B);
        }
        */
        /*
            Añade una coordenada 3D
        
        void PushCoor3D(Coor3D coors){
            vertexs.push_back(coors.x);
            vertexs.push_back(coors.y);
            vertexs.push_back(coors.z);
        }
        */
        /*
            Añade una coordenada 3D y un color a la vez al conjunto de vértices
        
        void pushCoor3DWRGB(Coor3D coor, RGBColor color){
            PushCoor3D(coor);
            PushColor(color);
        }
        */
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
        
        void PushTriangle(Coor3D A, Coor3D B, Coor3D C){
            PushCoor3D(A);
            PushCoor3D(B);
            PushCoor3D(C);
        }
        */
        /*
            Guarda datos escenciales para el trazado del escenario (traza un poligono regular), usando indices
        
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
        */
        std::vector<Coor3D> setRegular(std::vector<Coor3D>& verts, float radius, unsigned int vnumber){
            Coor3D currentcoor;
            currentcoor.x=0.0f;
            currentcoor.y=0.0f;
            currentcoor.z=0.0f;
            float anglex = (float)(4*acos(0.0)/vnumber);
            verts.push_back(currentcoor);
            for (int i=0; i<vnumber; i++){
                currentcoor.x=radius*cos(anglex*i);
                currentcoor.y=radius*sin(anglex*i);
                verts.push_back(currentcoor);
            }
            reserveArgSpace();
            return verts;
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
        std::vector<float> createTriangles(std::vector<Coor3D>coors){
            for(int i=1; i<(coors.size()-1); i++){
                PushTriangle(coors.at(0), coors.at(i), coors.at(i+1));
            }
            PushTriangle(coors.at(0), coors.at(coors.size()-1), coors.at(1));
            return vertexs;
        }
        */
        /*
            Guarda datos escenciales para el trazado del escenario (traza un poligono regular), con vertices puros
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
        */
        /*
            Guarda datos escenciales para el trazado del nuevo escenario (traza un poligono regular), con vertices puros
        
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
            }else{                                      //Increase
                for(int i=0; i<(vnumber-this->vnumber); i++){
                    cvcoors.push_back(cvcoors.back());
                }
                vertexs.clear();
                for(auto& coor : cvcoors){
                    pushCoor3D(vertexs, coor);
                }             
            }
            reserveArgSpace();
            return toverts;
        }
        */
        std::vector<Coor3D> setNewRegular(std::vector<Coor3D>& verts, std::vector<Coor3D>& toverts, float radius, unsigned int vnumber){
            //std::vector<Coor3D> cvcoors=verts;         //Guarda las coordenadas anteriores
            //Reinicia las coordenadas
            //verts.clear();
            toverts.clear();
            tempcoors.clear();
            //Logica sacada otra vez para formar el nuevo poligono
            Coor3D currentcoor;
            currentcoor.x=0.0f;
            currentcoor.y=0.0f;
            currentcoor.z=0.0f;
            float anglex = (float)(4*acos(0.0)/vnumber);
            //verts.push_back(currentcoor);
            toverts.push_back(currentcoor);
            tempcoors.push_back(currentcoor);
            for (int i=0; i<vnumber; i++){
                currentcoor.x=radius*cos(anglex*i);
                currentcoor.y=radius*sin(anglex*i);
                //verts.push_back(currentcoor);
                toverts.push_back(currentcoor);
                tempcoors.push_back(currentcoor);
            }
            //Evalua los casos en los que debe reducir el numero de poligonos
            if(this->vnumber>=vnumber){                 //Decrease
                for(int i=0; i<(this->vnumber-vnumber); i++){
                    toverts.push_back(toverts.back());
                }            
            }else{                                      //Increase
                for(int i=0; i<(vnumber-this->vnumber); i++){
                    verts.push_back(verts.back());
                }           
            }
            return toverts;
        }
        /*
            Crea los triangulos de manera bruta para la manera CLASSIC
        
        std::vector<float> createTriangles(std::vector<float>&vertexs, std::vector<Coor3D>coors){
            for(int i=1; i<(coors.size()-1); i++){
                PushTriangle(coors.at(0), coors.at(i), coors.at(i+1));
            }
            PushTriangle(coors.at(0), coors.at(coors.size()-1), coors.at(1));
            return vertexs;
        }
        */
        /*
            Inserta los colores en las coordenadas de las posiciones con algo de estilo
        
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
        */
        void addColors(unsigned int vnum, unsigned int timesto, std::vector<RGBColor>&colors){
            //std::cout << "Numero de vertices: " << vnum << std::endl;
            vertexcolors.clear();           //Limpio primero que nada
            int checkin = 0;
            RGBColor newColor;
            for(int i=0; i<vnum; i++){
                //std::cout << "Insertando en index: " << (3 + i* offset) << std::endl;
                newColor = setColorPattern(checkin, timesto, colors);
                pushColor(vertexcolors, newColor);
                checkin++;
            }
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
        /*
            Aniade color a la pared
        
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
        */ 
        void addWallColor(unsigned int vnum, RGBColor color){
            //std::cout << "Numero de vertices: " << vnum << std::endl;
            wvertexcolors.clear();           //Limpio primero que nada
            for(int i=0; i<vnum; i++){
                //std::cout << "Insertando en index: " << (3 + i* offset) << std::endl;
                pushColor(wvertexcolors, color);
            }         
        }  
        /*
            Rellena las coordenadas para al iniciar el objeto
        
        std::vector<float> padCoors(std::vector<float>&vertexs, unsigned int vnum, std::vector<Coor3D>&coors){
            int stride = calculateStride();
            for(int i=0; i<vnum; i++){
                //std::cout << "Insertando en index: " << (3 + i* stride) << std::endl;
                insertCoor3DAt(vertexs, coors.at(i), argsused+i*stride);
            }
            reserveArgSpace();
            return vertexs;
        }
        */
    public:
        //Constructors
        Center()=default;
        Center(Engine* engine, Shader* shader, float radius, float padding,unsigned int vnum, unsigned int patterntimesto, std::vector<RGBColor>&colors, RGBColor bordercolor):
            engine(engine),
            ShaderCenter(shader)
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
            setRegular(wvcoors,radius,vnum);
            addWallColor(wvcoors.size(), bordercolor);
            wvertexs= setupMesh(wvcoors, wvertexcolors, wvcoors, wvertexcolors);
            wtovcoors=wvcoors;
            //Relleno
            setRegular(vcoors,cradius,vnum);
            addColors(vcoors.size(), timesto, colors);
            vertexs=setupMesh(vcoors, vertexcolors, vcoors, vertexcolors);
            tovcoors=vcoors;
            //Memoria del objeto
            IDs.push_back(engine->createBuffer(wvertexs,&indexes,12,argspace));
            IDs.push_back(engine->createBuffer(vertexs,&indexes,12,argspace));
            //Comentalo si quieres
            /*
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
            */
        }
        
        //Getters
        unsigned int getID(unsigned int index) const {
            return IDs.at(index);
        }
        /*
        const std::vector<float>&getVertexs() const {
            return vertexs;
        }
        */
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
        /*
            Renderizar/Mostrar
        */
        void show() {
            ShaderCenter->setMat4("Model", model);
            engine->renderPolygon(ShaderCenter, this->getID(0), indexes.size());
            engine->renderPolygon(ShaderCenter, this->getID(1), indexes.size());
        }
        /*
            Intercambia los colores de Center con los de su vecino
        */
        void swapColors(){
            std::rotate(vertexcolors.begin(), vertexcolors.begin()+timesto, vertexcolors.end());
            //engine->updateBufferColorWeight(this->getID(1),vertexcolors,1,argspace);
            vertexs = modMesh(vertexs, NULL, &vertexcolors, NULL, &vertexcolors);
            engine->modBuffer(this->getID(1),vertexs,NULL);
        }
        /*
            Reserva la posicion para realizar el morphing
        */
        void prepareCenterforDecrease(int sides){         
            //Valor temporal
            std::vector<Coor3D> wvcoorsc = wtovcoors;
            std::vector<Coor3D> vcoorsc = tovcoors;
            //Guardo nuevas coordenadas al buffer
            //Pared
            wtovcoors=setNewRegular(wvcoors, wtovcoors, radius, sides);
            wvertexs=modMesh(wvertexs, &wvcoorsc, NULL, &wtovcoors, NULL);
            engine->modBuffer(this->getID(0),wvertexs, &indexes);
            //Preparo vertexs para temas de consistencia
            addWallColor(tempcoors.size(), wallcolor);
            wvertexs=setupMesh(tempcoors, wvertexcolors, tempcoors, wvertexcolors);
            wvcoors=tempcoors;
            wtovcoors=tempcoors;
            //Relleno
            float cradius=radius-padding;
            tovcoors=setNewRegular(vcoors, tovcoors, cradius, sides);
            vertexs=modMesh(vertexs, &vcoorsc, NULL, &tovcoors, NULL);
            engine->modBuffer(this->getID(1),vertexs, &indexes);
            //Preparo vertexs para temas de consistencia
            addColors(tempcoors.size(), timesto, pcolors);
            vertexs=setupMesh(tempcoors, vertexcolors, tempcoors, vertexcolors);
            vcoors=tempcoors;
            tovcoors=tempcoors;
        }
        void prepareCenterforIncrease(int sides){
            //Valor temporal
            std::vector<Coor3D> wvcoorsc = wtovcoors;
            std::vector<Coor3D> vcoorsc = tovcoors;
            //Preparo vertexs para temas de consistencia
            //Pared
            wtovcoors=setNewRegular(wvcoorsc, wtovcoors, radius, sides);
            addWallColor(wvcoorsc.size(), wallcolor);
            wvertexs=setupMesh(wvcoorsc, wvertexcolors, wtovcoors, wvertexcolors);
            //Relleno
            timesto=sides+1;
            float cradius=radius-padding;
            tovcoors=setNewRegular(vcoorsc, tovcoors, cradius, sides);
            addColors(vcoorsc.size(), timesto, pcolors);
            vertexs=setupMesh(vcoorsc, vertexcolors, tovcoors, vertexcolors);
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