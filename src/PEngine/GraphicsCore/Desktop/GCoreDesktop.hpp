#ifndef GCORE_DESKTOP_HPP
#define GCORE_DESKTOP_HPP

#include "../include/GCore.hpp"
#include "Time.hpp"
#include "WindowManager.hpp"

class GCoreDesktop: public IGCore {
    private:
    protected:
        WindowManager* windowManager;
        Time* time;
    public:
        GCoreDesktop(){
            //windowManager = new WindowManager();
            std::cout<<"GCoreDesktop ha sido instanciado"<<std::endl;
        }
        ~GCoreDesktop(){
            delete windowManager;
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
