#include "Engine.hpp"

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
    for(unsigned int i=0; i<350; i++){
        keyStates[i]=false;
        keyStates[i]=false;
    }
}
bool Engine::consumeKey(unsigned int token){
    if(this->keyStates[token] && !this->keyPressed[token]){
        this->keyPressed[token]=true;
        return true;
    }else{
        return false;
    }
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
//Cierra la ventana
void Engine::closeWindow(){
    glfwSetWindowShouldClose(window, true);
} 
//Destruye la ventana
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
unsigned int Engine::createBuffer(const std::vector<glm::vec3>& verts, const std::vector<unsigned int>* indexes, unsigned int numargs, const std::vector<unsigned int>& argsspace){
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
void Engine::modBuffer(unsigned int VAO, const std::vector<glm::vec3>& verts, const std::vector<unsigned int>* indexes){
    Buffer* buffer = findBufferByVAO(VAO);
    buffer->update(verts, indexes);
};
//Sobrescribe todo el contenido del buffer
void Engine::updateBuffer(unsigned int VAO, const std::vector<WVertex3D>& verts, const std::vector<unsigned int>* indexes){
    Buffer* buffer = findBufferByVAO(VAO);
    buffer->updateAll(verts, indexes);
};
//Liberar contenido de cierto buffer por VAO
void Engine::eliminateBuffer(unsigned int VAO) {
    for (auto it = Buffers.begin(); it != Buffers.end(); ++it) {
        if (it->getVAO() == VAO) {
            it->free();        // liberar memoria del buffer si aplica
            Buffers.erase(it); // quitarlo del vector
            break;
        }
    } 
}
//Limpia todos los buffers
void Engine::clearBuffers() {
    auto vaos = getAllVAOs(Buffers);
    auto vbos = getAllVBOs(Buffers);
    auto ebos = getAllEBOs(Buffers);
    glDeleteVertexArrays(vaos.size(), vaos.data());
    glDeleteBuffers(vbos.size(), vbos.data());
    glDeleteBuffers(ebos.size(), ebos.data());
    Buffers.clear();
}
//Render Methods
//Establece el color de la pantalla
void Engine::rendWindowBackground(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
//Renderiza un lazo por puntos
void Engine::renderLasso(Shader* shader, unsigned int rVAO, unsigned int vertexcount){
    shader->use();
    glBindVertexArray(rVAO);
    glDrawArrays(GL_LINE_LOOP, 0, vertexcount);
    glBindVertexArray(0);
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