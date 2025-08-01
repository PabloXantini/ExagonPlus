#ifndef SHADER_RMANAGER_DESK_HPP
#define SHADER_RMANAGER_DESK_HPP

#include "../GraphicsCore/include/Shader.hpp"
#include "../include/IResourceManager.hpp"
#include "utils/FileReader.hpp"

#include <memory>
#include <unordered_map>

class ShaderManagerDesk : public IShaderManager {
    private:
        std::unique_ptr<IShader> loadShaderFromFile(const std::vector<std::pair<ShaderPart, const char*>>& files){
            std::vector<ShaderPartData> shaderData;
            try{
                for(const auto&[part, path] : files){
                    ShaderPartData partData;
                    partData.part = part;
                    partData.glslCode = readFile(path);
                    shaderData.push_back(partData);
                }
            }catch(std::ifstream::failure&error){
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << error.what() << std::endl;
            }
            auto newShader = shaderMaker->createShader();
            newShader->load(shaderData);
            return newShader;
        }
        /*
        //To deprecate
        std::unique_ptr<IShader> loadShaderFromFile(const char* vFilePath, const char* fFilePath, const char* gFilePath){
            std::string vertexCode;
            std::string fragmentCode;
            std::string geometryCode;
            try {
                vertexCode = readFile(vFilePath);
                fragmentCode = readFile(fFilePath);
                if(gFilePath){
                    geometryCode = readFile(gFilePath);
                }
                
            }catch(std::ifstream::failure&error){
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << error.what() << std::endl;
            }
            //Variables finales
            const char* vShaderCode = vertexCode.c_str();
            const char* fShaderCode = fragmentCode.c_str();
            const char* gShaderCode = geometryCode.c_str();
            //Crea el shader
            auto newShader = shaderMaker->createShader();
            newShader->compile(vShaderCode, fShaderCode, gShaderCode ? gShaderCode : nullptr);
            return newShader;
        }
        */
    public:
        ShaderManagerDesk(){}
        ~ShaderManagerDesk(){}
        IShader* loadShader(std::string name, const std::vector<std::pair<ShaderPart, const char*>>& files){
            shaderList[name] = loadShaderFromFile(files);
            return shaderList[name].get();
        }
        /*
        IShader* loadShader(std::string name, const char* vShaderFile, const char* fShaderFile, const char* gShaderFile){
            shaderList[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
            return shaderList[name].get();
        }
        */
        IShader* getShader(std::string name){
            auto res = shaderList.find(name);
            if (res==shaderList.end() || !res->second){
                shaderList.erase(res);
                std::cout<<"ERROR: Could not find shader with this name: "<<name<<std::endl;
                return nullptr;
            }
            return res->second.get();
        }
};

#endif