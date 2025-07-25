#ifndef GCORE_DESKTOP_HPP
#define GCORE_DESKTOP_HPP

#include "../include/GCore.hpp"
#include "WindowManager.hpp"

class GCoreDesktop: public IGCore {
    private:
    protected:
        WindowManager* windowManager;
    public:
        GCoreDesktop(){
            //windowManager = new WindowManager();
            std::cout<<"GCoreDesktop ha sido instanciado"<<std::endl;
        }
        ~GCoreDesktop(){
            delete windowManager;
        }
        WindowManager* getWinManager() override {
            return windowManager;
        }
};

#endif
