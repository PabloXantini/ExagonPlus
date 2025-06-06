#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#include "Buffer.hpp"
#include "Shader.hpp"
//#include "../../resource.h"
#include "ImageProcessor.hpp"
#include "../utils/Color.h"
#include "../utils/Position.h"

//Archivozz
#include <fstream>
//Utilidades
#include <iostream>
//#include <unordered_map>
#include <vector>

using json = nlohmann::json;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

class Engine {
    private:
        //Variables propias del motor
        unsigned int Rwidth = 1200;                 //Valor reservado para el ancho
        unsigned int Rheight = 900;                 //Valor reservado para el alto
        float GnearD=0.1f;                          //Valor por defecto del nearD
        float GfarD=100.f;                          //Valor por defecto del farD
        float GFOV=45.0f;                           //Valor por defecto del FOV
        std::vector<Buffer> Buffers={};             //Buffers por VAO generados
        std::vector<Shader*> Shaders={};            //Shaders generados
        GLFWwindow* window;                         //Ventana
        bool keyStates[1024];                       //Tokens de teclado
        bool keyPressed[1024];                      //Tokens procesados
        //Methods
        void setupShaders();
        GLFWimage load_icon(int resID);
    public:
        //Constructor
        Engine();
        //Getters
        std::vector<unsigned int> getAllVAOs(const std::vector<Buffer>& buffers) {
            std::vector<unsigned int> VAOs;
            VAOs.reserve(buffers.size());
            for (const auto& buffer : buffers) {
                VAOs.push_back(buffer.getVAO());
            }
            return VAOs;
        }     
        std::vector<unsigned int> getAllVBOs(const std::vector<Buffer>& buffers) {
            std::vector<unsigned int> VBOs;
            VBOs.reserve(buffers.size());
            for (const auto& buffer : buffers) {
                VBOs.push_back(buffer.getVBO());
            }
            return VBOs;
        }
        std::vector<unsigned int> getAllEBOs(const std::vector<Buffer>& buffers) {
            std::vector<unsigned int> EBOs;
            EBOs.reserve(buffers.size());
            for (const auto& buffer : buffers) {
                EBOs.push_back(buffer.getEBO());
            }
            return EBOs;
        }
        Buffer* findBufferByVAO(unsigned int VAO) {
            for (Buffer& buffer : Buffers) {
                if (buffer.getVAO() == VAO) {
                    return &buffer;
                }
            }
            return nullptr;
        }
        bool& getKey(unsigned int index){
            return keyStates[index];
        }
        bool& getKeyPressed(unsigned int index){
            return keyPressed[index];
        }
        //Setters
        void setKeyPressed(unsigned int index, bool state){
            keyPressed[index]=state;
        }
        void setFOV(float FOV){
            GFOV=FOV;
        }
        void setnearD(float nearD){
            GnearD=nearD;
        }
        void setfarD(float farD){
            GfarD=farD;
        }
        //Initilization
        bool init();
        //Linking
        bool linkGLAD();
        //Window Methods
        bool initWindow(int width, int height, const char* title);
        void setWindowsIcons(std::vector<int>& iconsID);
        void initWindowResizing();
        void resize(int width, int height);
        void blockFPS(int FPSRate);
        bool isWindowOpen();
        void closeWindow();
        void destroyWindow();
        void handle();
        void close();
        //Keyboard Methods
        void initKeyboardListening();
        bool consumeKey(unsigned int token);
        // Memory Methods
        // Buffers
        unsigned int createBuffer(const std::vector<WVertex3D>& verts, const std::vector<unsigned int>* indexes, unsigned int numargs, const std::vector<unsigned int>& argsspace);
        unsigned int createBuffer(const std::vector<glm::vec3>& verts, const std::vector<unsigned int>* indexes, unsigned int numargs, const std::vector<unsigned int>& argsspace);
        void modBuffer(unsigned int VAO, const std::vector<WVertex3D>& verts, const std::vector<unsigned int>* indexes);
        void modBuffer(unsigned int VAO, const std::vector<glm::vec3>& verts, const std::vector<unsigned int>* indexes);
        void updateBuffer(unsigned int VAO, const std::vector<WVertex3D>& verts, const std::vector<unsigned int>* indexes);
        void eliminateBuffer(unsigned int VAO);
        //Shaders
        void registerShader(Shader* shader);
        void clearBuffers();
        void clearShaders();
        //Graph Global Methods
        void setProjectionAll(float FOV, float aspect, float nearD, float farD);        
        void modifyPerspective(float FOV, float nearD, float farD);
        void setViewAll(float x, float y, float z);
        void rendWindowBackground();
        void renderLasso(Shader* shader, unsigned int rVAO, unsigned int vertexcount);
        void renderPolygon(Shader* shader, unsigned int rVAO, unsigned int sides);
        void renderPolygon2(Shader* shader, unsigned int rVAO, unsigned int vertexcount);
};

//Callbacks
//Pantalla
inline void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    if (height == 0) return;
    glViewport(0, 0, width, height);
    void* ptr = glfwGetWindowUserPointer(window);
    if (ptr) {
        Engine* engine = static_cast<Engine*>(ptr);
        engine->resize(width, height);  // Llama al método de la clase
    }
}
//Teclado
inline void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    //std::cout<<"Tecla: "<<key<<" Action: "<<action<<std::endl;
    void* ptr = glfwGetWindowUserPointer(window);
    if(ptr){
        Engine* engine = static_cast<Engine*>(ptr);
        if(key>=0 && key<1024){
            switch(action){
                case GLFW_PRESS:
                    engine->getKey(key)=true;
                    break;
                case GLFW_RELEASE:
                    engine->getKey(key)=false;
                    engine->getKeyPressed(key)=false;
                    break;
            }
        }
    }
}

#endif