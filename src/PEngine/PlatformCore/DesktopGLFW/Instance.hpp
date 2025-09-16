#ifndef GLFW_PLATFORM_INSTANCE_HPP
#define GLFW_PLATFORM_INSTANCE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../include/IPlatform.hpp"

#include "Time.hpp"
#include "WindowManager.hpp"

#include <iostream>

enum class API_SELECTED {
    OPEN_GL,
    OPEN_GL_ES,
    VULKAN,
    NONE
};

class CoreDesktopGLFW : public IPlatform {
    private:
        //Basic
        Time* time;
        WindowManager* WinManager;
        //Context
        API_SELECTED api = API_SELECTED::NONE;
        ContextManager* CtxManager = nullptr;

        //WindowRenderer* renderer
        API_SELECTED castString(std::string& api_name){
            if(api_name == "open_gl") return API_SELECTED::OPEN_GL;
            return API_SELECTED::NONE; 
        }
    public:
        CoreDesktopGLFW(){
            time = new Time();
            WinManager = new WindowManager(time);
            //inicia GLFW
            glfwInit();
            std::cout<<"Este codigo plataforma debe haberse inicializado"<<std::endl;
        };
        ~CoreDesktopGLFW(){
            delete WinManager;
            delete time;
            if(CtxManager) delete CtxManager;
            std::cout<<"Este codigo plataforma debe haberse limpiado"<<std::endl;
        };
        void setupGraphicsAPI(std::string& api_name, unsigned int major_version, unsigned int minor_version) override {
            api = castString(api_name);
            //This method in the future I should pass name parameter for select openGL or Vulkan

            //This is an OpenGL implementation
            CtxManager = new ContextManager();
            WinManager->init(major_version, minor_version);
        }
};

#endif