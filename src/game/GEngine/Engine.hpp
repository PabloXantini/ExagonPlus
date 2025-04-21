#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Buffer.hpp"
#include "Shader.hpp"
#include "Shaders.hpp"
#include "../../resource.h"
#include "../../ImageProcessor.cpp"
#include "../Color.h"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>

struct Coor3D {
    float x;
    float y;
    float z;
};

struct ObjectBuffer {
    unsigned int VAO; //Vertex Array Object: Define el objecto de vertices
    unsigned int VBO; //Vertex Buffer Object: Define en donde se van a guardar los vertices
    unsigned int EBO=0; //Element Buffer Object: Define como se van a dibujar los vertices
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Engine {
    private:
        //Variables propias del motor
        unsigned int Rwidth = 1200;                 //Valor reservado para el ancho
        unsigned int Rheight = 900;                 //Valor reservado para el alto
        float GnearD=0.1f;                          //Valor por defecto del nearD
        float GfarD=100.f;                          //Valor por defecto del farD
        float GFOV=45.0f;                           //Valor por defecto del FOV
        std::vector<ObjectBuffer> buffers={};       //Buffers generados
        std::vector<Buffer> Buffers={};             //Buffers de verdad generados
        std::map<ShaderName, unsigned int> shaders; //Posibility to deprecate
        std::unordered_map<int, bool> keyStates;    //Tokens de teclado
        GLFWwindow* window;                         //Ventana
        //Shaders usados
        //Shader BASIC;
        Shader* BASIC;
        //Methods
        void setupShaders();
        GLFWimage load_icon(int resID);
    public:
        //Constructor
        Engine();
        ~Engine();
        //Getters
        unsigned int getShaderProgram(ShaderName label){
            return shaders[label];
        }
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
        Buffer* findBufferByVBO(unsigned int VBO) {
            for (Buffer& buffer : Buffers) {
                if (buffer.getVBO() == VBO) {
                    return &buffer;
                }
            }
            return nullptr;
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
        void init();
        void handle();
        void close();
        //Keyboard Methods
        void pollInput();
        bool isKeyPressed(int key);
        //Memory Methods
        unsigned int createBuffer(const std::vector<float>& verts, const std::vector<unsigned int>* indexes, unsigned int numargs, const std::vector<unsigned int>& argsspace);
        ObjectBuffer createBuffer3D(const std::vector<float>& verts, const std::vector<unsigned int>* indexes, bool hasColor);
        void updateBuffer(unsigned int VBO, const std::vector<float>& verts, const std::vector<unsigned int>* indexes);
        void updateBufferColorWeight(unsigned int VAO, std::vector<RGBColor>& colors,unsigned int atribindex, const std::vector<unsigned int>& argsspace);
        void updateBufferCoorWeight(unsigned int VBO, std::vector<Coor3D>& coors, unsigned int atribindex, const std::vector<unsigned int>& argsspace);
        void initShaders();
        void initializeCustom(float radius);
        void clearBuffers();
        void clearShaders();
        //Graph Methods
        void fixScreenProportion(GLFWwindow* window);
        void setPerspective(float FOV, float aspect, float nearD, float farD);
        //void setupPerspective(float FOV, float aspect, float nearD, float farD);
        void modifyPerspective(float FOV, float nearD, float farD);
        void setupView(float x, float y, float z);
        void translateView(float x, float y, float z);
        void rendWindowBackground();
        void renderPolygon(unsigned int rVAO, unsigned int sides);
        void renderPolygon2(unsigned int rVAO, unsigned int vertexcount);
        void rotate3D(float time, float RX, float RY, float RZ);
        void setupscale3D(float factor);
        void scale3D(float factor);
        void polygonRadiusPolarMorph3D(float radius, float step);
        void changeHue(float change, float hueFactor, float hueSpeed);
};

//Callback
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

Engine::Engine(){
    std::cout<<"Oh me creooo, dice Engine o Motor"<<std::endl;
}
Engine::~Engine(){
    delete BASIC;
}
//Posibilly to deprecate
void Engine::setupShaders(){
    //Aqui se supone que cargo dinamicamente los shaders
    //Si se me complica manejar los shader aca, lo borro
}
void Engine::initShaders(){
    BASIC = new Shader(IDR_VSHADER2,IDR_FSHADER2);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
//Coreccion de reescalado
void Engine::resize(int width, int height){
    Rwidth=width;
    Rheight=height;
    float aspect = (float)width / (float)height;
    setPerspective(GFOV, aspect, GnearD, GfarD);
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
//Keyboard Methods
//Seteo de Teclas
void Engine::pollInput() {
    for (int key = 0; key < 350; ++key)
        keyStates[key] = glfwGetKey(window, key) == GLFW_PRESS;
}
//Checar que numero de tecla se activo
bool Engine::isKeyPressed(int key) {
    return keyStates[key];
}
//Memory Methods
//Crea un buffer para un objeto - Posibililly to deprecate
ObjectBuffer Engine::createBuffer3D(const std::vector<float>& verts, const std::vector<unsigned int>* indexes, bool hasColor){
    struct ObjectBuffer newBuffer;

    //Asigno IDs para VAO, VBO, EBO
    glGenVertexArrays(1, &newBuffer.VAO);
    glGenBuffers(1, &newBuffer.VBO);
    //Opcional
    if(indexes) glGenBuffers(1, &newBuffer.EBO);

    //Asignacion de memoria para VAO
    glBindVertexArray(newBuffer.VAO);
    //Asignacion de memoria para VBO
    glBindBuffer(GL_ARRAY_BUFFER, newBuffer.VBO);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);
    //Opcional: Asignacion de memoria para EBO
    if(indexes){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newBuffer.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes->size() * sizeof(unsigned int), indexes->data(), GL_STATIC_DRAW);
    }
    //Setup de argumentos para el buffer
    if(hasColor){
        //Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        //Color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
        glEnableVertexAttribArray(1);
    }else{
        //Color
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
    //Desvincular
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //Faltaria que se guarden esos datos en un variable de objetos
    buffers.push_back(newBuffer);

    return newBuffer;
}
//Crea un buffer para un objeto dado argumentos
unsigned int Engine::createBuffer(const std::vector<float>& verts, const std::vector<unsigned int>* indexes, unsigned int numargs, const std::vector<unsigned int>& argsspace){
    Buffer newBuffer(verts, indexes, numargs);
    for(auto& arg : argsspace){
        newBuffer.addAttribute(arg);
    }
    Buffers.push_back(std::move(newBuffer));
    return newBuffer.getVAO();
}
//Actualiza todo el contenido del buffer
void Engine::updateBuffer(unsigned int VBO, const std::vector<float>& verts, const std::vector<unsigned int>* indexes){
    Buffer* buffer = findBufferByVBO(VBO);
    buffer->updateAll(verts, indexes);
};
//Actualiza el peso de colores
void Engine::updateBufferColorWeight(unsigned int VBO, std::vector<RGBColor>& colors, unsigned int atribindex, const std::vector<unsigned int>& argsspace){
    Buffer* buffer = findBufferByVBO(VBO);
    int start=0;
    for(int i=0;i<atribindex;i++){
        start+=argsspace.at(i);
    }
    int colorsize=argsspace.at(atribindex);
    int stride=buffer->getArgSize();
    std::vector<float> colorspace;
    for (auto& c : colors){
        pushColor(colorspace, c);
    }
    //Abre el buffer en cuestion
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    for (size_t i=0; i<colors.size();++i) {
        GLintptr offset = start*sizeof(float) + i*stride*sizeof(float);
        glBufferSubData(GL_ARRAY_BUFFER, offset, colorsize*sizeof(float), &colorspace[i*colorsize]);
    }
    //Desvincula en buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Engine::updateBufferCoorWeight(unsigned int VBO, std::vector<Coor3D>& coors, unsigned int atribindex, const std::vector<unsigned int>& argsspace){
    Buffer* buffer = findBufferByVBO(VBO);
    int start=0;
    for(int i=0;i<atribindex;i++){
        start+=argsspace.at(i);
    }
    int coorsize=argsspace.at(atribindex);
    int stride=buffer->getArgSize();
    std::vector<float> coorspace;
    for (auto& coor : coors){
        coorspace.push_back(coor.x);
        coorspace.push_back(coor.y);
        coorspace.push_back(coor.z);
    }
    //Abre el buffer en cuestion
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    for (size_t i=0; i<coors.size();++i) {
        GLintptr offset = start*sizeof(float) + i*stride*sizeof(float);
        glBufferSubData(GL_ARRAY_BUFFER, offset, coorsize*sizeof(float), &coorspace[i*coorsize]);
    }
    //Desvincula en buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
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
void Engine::renderPolygon(unsigned int rVAO, unsigned int nindexes) {
    BASIC->use();
    glBindVertexArray(rVAO);
    glDrawElements(GL_TRIANGLES, nindexes, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
//Renderiza un poligono con vertices
void Engine::renderPolygon2(unsigned int rVAO, unsigned int vertexcount){
    BASIC->use();
    glBindVertexArray(rVAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexcount);
    glBindVertexArray(0);
}
//Arregla la resolucion de pantalla
void Engine::fixScreenProportion(GLFWwindow* window){
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float aspect = (float)width / (float)height;
    setPerspective(45.0f, aspect, 0.1f, 100.0f);
}
//Transformaciones Perpespectiva
//Establecer perspectiva con las proporciones de la pantalla
void Engine::setPerspective(float FOV, float aspect, float nearD, float farD){
    BASIC->use();
    glm::mat4 projection = glm::mat4(1.0);
    projection = glm::perspective(glm::radians(FOV), aspect, nearD, farD);
    BASIC->setMat4("transProjection",projection);
}
void Engine::modifyPerspective(float FOV, float nearD, float farD){
    float aspect = (float)Rwidth/(float)Rheight;
    setPerspective(FOV, aspect, nearD, farD);
}
//Transformaciones Vista
//Mover camara
void Engine::setupView(float x, float y, float z){
    BASIC->use();
    glm::mat4 view = glm::mat4(1.0);
    view = glm::lookAt(glm::vec3(x, y, z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    BASIC->setMat4("transView",view);
}
void Engine::translateView(float x, float y, float z){
    glm::mat4 view = glm::mat4(1.0);
    view = glm::translate(view, glm::vec3(x, y, z));
    BASIC->setMat4("transView",view);
}
//Transformaciones Modelo
//Rotacion en 3 dimensiones
void Engine::rotate3D(float time, float RX, float RY, float RZ){
    glm::mat4 rot = glm::mat4(1.0);
    rot = glm::rotate(rot, glm::radians(time*RX), glm::vec3(1.0,0.0,0.0)); //Rotation en el eje X
    rot = glm::rotate(rot, glm::radians(time*RY), glm::vec3(0.0,1.0,0.0)); //Rotation en el eje Y
    rot = glm::rotate(rot, glm::radians(time*RZ), glm::vec3(0.0,0.0,1.0)); //Rotation en el eje Z
    BASIC->setMat4("transRotation",rot);
}
//Escalado
void Engine::setupscale3D(float factor){
    BASIC->use();
    glm::mat4 sc = glm::mat4(1.0);
    sc = glm::scale(sc, glm::vec3(factor));
    BASIC->setMat4("transScale",sc);
}
//Escalado
void Engine::scale3D(float factor){
    glm::mat4 sc = glm::mat4(1.0);
    sc = glm::scale(sc, glm::vec3(factor));
    BASIC->setMat4("transScale",sc);
}
void Engine::polygonRadiusPolarMorph3D(float radius, float step){
    BASIC->setFloat("radius",radius);
    BASIC->setFloat("morphprogress",step);
}
//Cambia el HUE del escenario
void Engine::changeHue(float time, float hueFactor, float hueSpeed){
    BASIC->setFloat("uTime",time);
    BASIC->setFloat("HueFactor",hueFactor);
    BASIC->setFloat("HueSpeed",hueSpeed);
}
//Eliminar shaders
void Engine::clearShaders(){
    BASIC->kill();
}
//Cierra el motor
void Engine::close(){
    clearBuffers();
    clearShaders();
}
//Metodos fuera del scope
void Engine::initializeCustom(float radius){
    BASIC->use();
    BASIC->setFloat("radius",radius);
    BASIC->setFloat("morphprogress",0.0f);
}

#endif