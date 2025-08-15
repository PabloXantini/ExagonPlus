#ifndef GCORE_DESKTOP_HPP
#define GCORE_DESKTOP_HPP

#include "../include/GCore.hpp"
#include "Time.hpp"
#include "WindowManager.hpp"

class GCoreDesktop: public IGCore {
    private:
    protected:
        WindowManager* windowManager;
        ContextManager* contextManager;
        Time* time;
    public:
        GCoreDesktop(){
            std::cout<<"GCoreDesktop ha sido instanciado"<<std::endl;
            //Inicia GLFW
            glfwInit();
        }
        ~GCoreDesktop(){
            delete windowManager;
            delete contextManager;
            delete time;
        }
        WindowManager* getWinManager() override {
            return windowManager;
        }
        Time* manageTime() override {
            return time;
        }
};

#endif
