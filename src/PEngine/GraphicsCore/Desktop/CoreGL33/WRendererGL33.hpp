#ifndef W_R_GL_33_HPP
#define W_R_GL_33_HPP

#include "../WindowManager.hpp"

class WindowRendererGL33 : public WindowManager {
    private:
    public:
        WindowRendererGL33(Time* time): WindowManager(time)
        {
             std::cout<<"El gestor de ventanas se ha instanciado"<<std::endl;
        }
        ~WindowRendererGL33(){
            std::cout<<"El gestor de ventanas se ha limpiado"<<std::endl;
        }
        void setGLconfig(Window* window) override {
            if(!window){
                return;
            }
            glViewport(0, 0, window->getWidth(), window->getHeight());
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        void renderInWindow() override {
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }
};

#endif