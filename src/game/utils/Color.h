#ifndef COLOR_H
#define COLOR_H

#include <vector>

struct RGBColor {
    float R;
    float G;
    float B;
};

/*
    Añade un color a la mezcla de vertices, en base a un vector determinado
*/
inline void pushColor(std::vector<float>&vertexs, RGBColor color){
    vertexs.push_back(color.R);
    vertexs.push_back(color.G);
    vertexs.push_back(color.B);
}
/*
    Añade un color a la mezcla de vertices, en base a un vector de Colores determinado
*/
inline void pushColor(std::vector<RGBColor>&colors, RGBColor color){
    colors.push_back(color);
}
/*
    Añade un color a la mezcla de vertices, dependiendo del desplazamiento
*/
inline void insertColorAt(std::vector<float>&vertexs, RGBColor color, int offset){
    vertexs.insert(vertexs.begin()+offset, color.R);
    vertexs.insert(vertexs.begin()+offset+1, color.G);
    vertexs.insert(vertexs.begin()+offset+2, color.B);
}

#endif