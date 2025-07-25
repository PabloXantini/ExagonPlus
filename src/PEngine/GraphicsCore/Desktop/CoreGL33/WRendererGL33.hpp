#ifndef W_R_GL_33_HPP
#define W_R_GL_33_HPP

#include "../WindowManager.hpp"

class WindowRenderer : public WindowManager {
    public:
        WindowRenderer(){}
        ~WindowRenderer(){}
        void setGLconfig(Window* window) override {
            if(!window){
                return;
            }
            glViewport(0, 0, window->getWidth(), window->getHeight());
        }
        void renderInWindow() override {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }
};

#endif