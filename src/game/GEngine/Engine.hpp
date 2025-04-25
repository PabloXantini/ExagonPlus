#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Buffer.hpp"
#include "Shader.hpp"
//#include "../../resource.h"
#include "../../ImageProcessor.cpp"
#include "../utils/Color.h"
#include "../utils/Position.h"

#include <iostream>
//#include <unordered_map>
#include <vector>

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
        bool keyStates[350];                        //Tokens de teclado
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
        //Setters
        void setFOV(float FOV){
            GFOV=FOV;
        }
        void setnearD(float nearD){
            GnearD=nearD;
        }
        void setfarD(float farD){
            GfarD=farD;
        }
        //Linking
        bool linkGLAD();
        //Window Methods
        bool initWindow(int width, int height, const char* title);
        void setWindowsIcons(std::vector<int>& iconsID);
        void initWindowResizing();
        void resize(int width, int height);
        void blockFPS(int FPSRate);
        bool isWindowOpen();
        void destroyWindow();
        void handle();
        void close();
        //Keyboard Methods
        void initKeyboardListening();
        //Memory Methods
        //Buffers
        unsigned int createBuffer(const std::vector<float>& verts, const std::vector<unsigned int>* indexes, unsigned int numargs, const std::vector<unsigned int>& argsspace);
        unsigned int createBuffer(const std::vector<WVertex3D>& verts, const std::vector<unsigned int>* indexes, unsigned int numargs, const std::vector<unsigned int>& argsspace);
        void modBuffer(unsigned int VAO, const std::vector<WVertex3D>& verts, const std::vector<unsigned int>* indexes);
        void updateBuffer(unsigned int VAO, const std::vector<WVertex3D>& verts, const std::vector<unsigned int>* indexes);
        //Shaders
        void registerShader(Shader* shader);
        void clearBuffers();
        void clearShaders();
        //Graph Global Methods
        void setProjectionAll(float FOV, float aspect, float nearD, float farD);        
        void modifyPerspective(float FOV, float nearD, float farD);
        void setViewAll(float x, float y, float z);
        void rendWindowBackground();
        void renderPolygon(Shader* shader, unsigned int rVAO, unsigned int sides);
        void renderPolygon2(Shader* shader, unsigned int rVAO, unsigned int vertexcount);
};

//Callbacks
//Pantalla
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    if (height == 0) return;
    glViewport(0, 0, width, height);
    void* ptr = glfwGetWindowUserPointer(window);
    if (ptr) {
        Engine* engine = static_cast<Engine*>(ptr);
        engine->resize(width, height);  // Llama al método de la clase
    }
    //std::cout<<"Cambio"<<std::endl;
}
//Teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    void* ptr = glfwGetWindowUserPointer(window);
    if(ptr){
        Engine* engine = static_cast<Engine*>(ptr);
        if(key==GLFW_KEY_ESCAPE && action==GLFW_PRESS){
            glfwSetWindowShouldClose(window, true);
        }
        if(key>=0 && key<350){
            if(action==GLFW_PRESS){
                engine->getKey(key)=true;
            } else if(action==GLFW_RELEASE){
                engine->getKey(key)=false;
            }
        }
    }
}

Engine::Engine(){
    std::cout<<"Oh me creooo, dice Engine o Motor"<<std::endl;
}
//Private methods
GLFWimage Engine::load_icon(int resID) {
    GLFWimage image;
    int width, height;
    image.pixels = loadImage(resID, width, height);
    image.width = width;
    image.height = height;
    return image;
}
//Link Methods
//Evalua si arranco GLAD(El linker para usar OpenGL)
bool Engine::linkGLAD(){
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}
//Window Methods
//Crea una ventana
bool Engine::initWindow(int width, int height, const char* title){
    //Inicializa el contexto de la pantalla
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    //Le dice a OpenGL cual es la ventana que va a renderizar
    glfwMakeContextCurrent(window);
    return true;
}
//Aniade iconos a la aplicacion
void Engine::setWindowsIcons(std::vector<int>& iconsID){
    if (!window) {
        std::cout << "GLFW window don't exists" << std::endl;
        return;
    }
    std::vector<GLFWimage> icons(iconsID.size());
    for (size_t i = 0; i < iconsID.size(); ++i) {
        icons[i] = load_icon(iconsID[i]);
    }
    glfwSetWindowIcon(window, static_cast<int>(icons.size()), icons.data());
    for (auto& icon : icons) {
        delete[] icon.pixels;
    }
}
//Inicia el reescalado
void Engine::initWindowResizing(){
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}
void Engine::initKeyboardListening(){
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, key_callback);
}
//Coreccion de reescalado
void Engine::resize(int width, int height){
    Rwidth=width;
    Rheight=height;
    float aspect = (float)width / (float)height;
    setProjectionAll(GFOV, aspect, GnearD, GfarD);
}
//Bloquea los FPS
void Engine::blockFPS(int FPSRate){
    if(FPSRate==0){
        std::cout << "FPS block not sucessfull" << std::endl;
        return;
    }  
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int refreshRate = mode->refreshRate;
    if (mode) {
        std::cout << "Refresh Rate: " << mode->refreshRate << " Hz" << std::endl;
    }
    int block = refreshRate/FPSRate;
    glfwSwapInterval(block);
}
//Ventana abierta
bool Engine::isWindowOpen(){
    return !glfwWindowShouldClose(window);
}
//Destruye la ventan
void Engine::destroyWindow(){
    glfwTerminate();
}
//Controlador del motor
void Engine::handle(){
    glfwSwapBuffers(window);
    glfwPollEvents();
}

//Memory Methods
//Registra un shader para que lo reconozca la clase
void Engine::registerShader(Shader* shader){
    Shaders.push_back(shader);
};
//Crea un buffer para un objeto dado argumentos
unsigned int Engine::createBuffer(const std::vector<WVertex3D>& verts, const std::vector<unsigned int>* indexes, unsigned int numargs, const std::vector<unsigned int>& argsspace){
    Buffer newBuffer(verts, indexes, numargs);
    for(auto& arg : argsspace){
        newBuffer.addAttribute(arg);
    }
    Buffers.push_back(std::move(newBuffer));
    return newBuffer.getVAO();
}
//Actualiza todo el contenido del buffer
void Engine::modBuffer(unsigned int VAO, const std::vector<WVertex3D>& verts, const std::vector<unsigned int>* indexes){
    Buffer* buffer = findBufferByVAO(VAO);
    buffer->update(verts, indexes);
};
//Sobrescribe todo el contenido del buffer
void Engine::updateBuffer(unsigned int VAO, const std::vector<WVertex3D>& verts, const std::vector<unsigned int>* indexes){
    Buffer* buffer = findBufferByVAO(VAO);
    buffer->updateAll(verts, indexes);
};
//Limpia todos los buffers
void Engine::clearBuffers() {
    auto vaos = getAllVAOs(Buffers);
    auto vbos = getAllVBOs(Buffers);
    auto ebos = getAllEBOs(Buffers);
    glDeleteVertexArrays(vaos.size(), vaos.data());
    glDeleteBuffers(vbos.size(), vbos.data());
    glDeleteBuffers(ebos.size(), ebos.data());
}
//Render Methods
//Establece el color de la pantalla
void Engine::rendWindowBackground(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
//Renderiza un poligono con indices
void Engine::renderPolygon(Shader* shader, unsigned int rVAO, unsigned int nindexes) {
    shader->use();
    glBindVertexArray(rVAO);
    glDrawElements(GL_TRIANGLES, nindexes, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
//Renderiza un poligono con vertices
void Engine::renderPolygon2(Shader* shader, unsigned int rVAO, unsigned int vertexcount){
    shader->use();
    glBindVertexArray(rVAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexcount);
    glBindVertexArray(0);
}
//Transformaciones Perpespectiva
//Establecer perspectiva con las proporciones de la pantalla
void Engine::setProjectionAll(float FOV, float aspect, float nearD, float farD){
    for(Shader* shader : Shaders){
        shader->use();
        glm::mat4 projection = glm::mat4(1.0);
        projection = glm::perspective(glm::radians(FOV), aspect, nearD, farD);
        shader->setMat4("Projection",projection);
    }  
}
//Modificar la perspectiva globalmente
void Engine::modifyPerspective(float FOV, float nearD, float farD){
    float aspect = (float)Rwidth/(float)Rheight;
    setProjectionAll(FOV, aspect, nearD, farD);
}
//Transformaciones Vista
//Mover camara
void Engine::setViewAll(float x, float y, float z){
    for(Shader* shader : Shaders){
        shader->use();
        glm::mat4 view = glm::mat4(1.0);
        view = glm::lookAt(glm::vec3(x, y, z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shader->setMat4("View",view);
    }  
}

//Eliminar shaders
void Engine::clearShaders(){
    for(Shader* shader : Shaders){
        if(shader){
            shader->kill();
            //delete shader;
        }
    }
    Shaders.clear();
    //BASIC->kill();
}
//Cierra el motor
void Engine::close(){
    clearBuffers();
    clearShaders();
}

#endif