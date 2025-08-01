#ifndef SHADER_MAKER_GL33_HPP
#define SHADER_MAKER_GL33_HPP

#include "../../include/GCore.hpp"
#include "Shader33.hpp"

class ShaderMakerGL33 : public IShaderMaker {
    public:
        ShaderMakerGL33()=default;
        ~ShaderMakerGL33()=default;
        std::unique_ptr<IShader> createShader() override {
            return std::make_unique<ShaderGL33>();
        }
};

#endif