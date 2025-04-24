#ifndef POSITION_H
#define POSITION_H

#include <vector>

struct Coor3D {
    float x;
    float y;
    float z;
};

/*
    Añade una coordenada 3D, en base a un vector determinado
*/
void pushCoor3D(std::vector<float>&vertexs, Coor3D coors){
    vertexs.push_back(coors.x);
    vertexs.push_back(coors.y);
    vertexs.push_back(coors.z);
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
    Crea un triangulo y la aniade a la malla
*/
void pushTriangle(std::vector<Coor3D>& mesh, Coor3D A, Coor3D B, Coor3D C){
    mesh.push_back(A);
    mesh.push_back(B);
    mesh.push_back(C);
}
#endif