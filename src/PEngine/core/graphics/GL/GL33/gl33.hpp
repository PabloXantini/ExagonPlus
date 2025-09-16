#ifndef GL_33_BACKEND_HPP
#define GL_33_BACKEND_HPP

#include "../../include/Graphics.hpp"

class GL33 : public IGraphics {
    private:
    public:
        GL33(){
            std::cout<<"Graphics: Selecting OpenGL33"<<std::endl;

        }
        ~GL33(){
            std::cout<<"Graphics: Closed OpenGL33"<<std::endl;
        }
};

#endif