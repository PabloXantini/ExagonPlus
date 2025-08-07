#ifndef RENDERER_MAKER_GL33_HPP
#define RENDERER_MAKER_GL33_HPP

#include "../../include/GCore.hpp"
#include "MeshRenderer33.hpp"

class RendererMaker33 : public IRendererMaker {
    public:
        RendererMaker33(){};
        ~RendererMaker33(){};
        Renderer* makeRenderer(IShader* shader) override {
            return new MeshRenderer33(shader);
        }
};

#endif