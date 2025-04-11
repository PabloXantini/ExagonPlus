#ifndef BG_HPP
#define BG_HPP

#include <vector>

class BG{
public:
    BG();
    const std::vector<float>&getVertex() const;
private:
    std::vector<float> vertexs;
};

BG::BG() {
    vertexs = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
}

const std::vector<float>& BG::getVertex() const {
    return vertexs;
}

#endif