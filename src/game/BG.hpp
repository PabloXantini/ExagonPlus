#ifndef BG_HPP
#define BG_HPP

#include "Engine.hpp"

#include <vector>

class BG{
    private:
        std::vector<float> vertexs = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f
        };
        unsigned int vnumber = vertexs.size();
        Engine engine;
    public:
        //Constructors
        BG()=default;
        BG(const std::vector<float> vxs){
            vertexs=vxs;
        }
        //Getters
        const std::vector<float>&getVertexs() const {
            return vertexs;
        }
        const unsigned int&getVertexCount() const {
            return vnumber;
        }
        //Setters
        void setVertexs(std::vector<float> vxs) {
            vertexs=vxs;
        }
        //Mostrar
        void show(unsigned int rVAO){
            engine.renderPolygon(rVAO, engine.shaderProgram, vnumber);
        }
};

#endif