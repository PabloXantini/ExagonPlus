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
    public:
};

#endif