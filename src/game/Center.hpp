#ifndef CENTER_HPP
#define CENTER_HPP

#include "GEngine/Engine.hpp"
#include "BG.hpp"

class Center : public BG {
    private:
        std::vector<unsigned int> IDs={};           //Esto me permite saber que IDs tienen cada forma que vaya a renderizar
        std::vector<unsigned int> argspace={3,3,3}; //Pos//Color//toPos
        unsigned int argsused=0;
        unsigned int argpointer=0;

        std::vector<unsigned int> indexes={};       //Indices de generacion
        std::vector<float> vertexs={};              //Vertices brutos del objeto

        std::vector<Coor3D> vcoors={};              //Coordenadas 3D POR VERTICE
        std::vector<Coor3D> allvcoors={};           //Coordenadas 3D POR VERTICE
        std::vector<Coor3D> allvcoorscopy={};       //Copia Coordenadas 3D POR VERTICE

        unsigned int vnumber = 3;
        float radius=1.2f;
        RGBColor pcolor;
        
        //Objetos de referencia
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
        void PushColor(RGBColor color){
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
    public:
};

#endif