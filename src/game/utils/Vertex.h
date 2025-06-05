#ifndef VERTEX_H
#define VERTEX_H

#include "Color.h"
#include "Position.h"

struct WVertex3D {
    Coor3D Pos;
    RGBColor Color;
    Coor3D toPos;
    RGBColor toColor;
};
/*
    Aniade un vertice con peso
*/
inline void pushWVertex(std::vector<WVertex3D>& vertexs, Coor3D coor1, RGBColor color1, Coor3D coor2, RGBColor color2){
    WVertex3D vertex;
    vertex.Pos = coor1;
    vertex.Color = color1;
    vertex.toPos = coor2;
    vertex.toColor = color2;
    vertexs.push_back(vertex);
}
/*
    Aniade un Color
*/
inline void putColor(WVertex3D& vertex, RGBColor color){
    vertex.Color = color;
}
inline void putToColor(WVertex3D& vertex, RGBColor color){
    vertex.toColor = color;
}
/*
    Aniade una Posicion
*/
inline void putPosition(WVertex3D& vertex, Coor3D coor){
    vertex.Pos = coor;
}
inline void putToPosition(WVertex3D& vertex, Coor3D coor){
    vertex.toPos = coor;
}

#endif