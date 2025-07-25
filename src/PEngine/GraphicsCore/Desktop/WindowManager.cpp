#include "WindowManager.hpp"

bool WindowManager::init(int GLmajorVersion, int GLminorVersion){
    //Establece la version del contexto de OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLmajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLminorVersion);
    //Windows, Linux
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //MacOS
    //glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_TRUE);
    //Checa el estado de los monitores
    checkMonitors();
    return true;   
}

Window* WindowManager::createWindow(unsigned int width, unsigned int height, const char* title, bool fullscreen, unsigned int monitorIndex, Window* windowShared){
    GLFWmonitor* monitorSelected = nullptr;
    Window* newWindow;
    if(fullscreen){
        checkMonitors();
        if (monitorIndex > 0 && monitorIndex <= (unsigned int)(monitorCount)){
            monitorSelected = allMonitors[monitorIndex-1];
            const GLFWvidmode* mode = glfwGetVideoMode(monitorSelected);
            width = mode->width;
            height = mode->height;
        }
    }
    //Genera una ventana
    newWindow = new Window(width, height, title, monitorSelected, windowShared);
    if(!GLADLinked){
        GLADLinked = linkGLAD();
        if(!GLADLinked) {
            delete newWindow;
            return nullptr;
        }
    }
    return newWindow;
}

void WindowManager::runAsOnlyWindow(Window* mainWindow){
    setGLconfig(mainWindow);
    glfwSwapInterval(1);
    while(!glfwWindowShouldClose(mainWindow->getWindowReference())){
        glfwPollEvents();
        renderInWindow();
        glfwSwapBuffers(mainWindow->getWindowReference());
    }
    glfwTerminate();
}

bool WindowManager::linkGLAD(){
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ERROR: FAILED TO INITIALIZE GLAD" << std::endl;
        return false;
    }
    return true;
}

void WindowManager::checkMonitors(){
    allMonitors = glfwGetMonitors(&monitorCount);
    if(allMonitors && monitorCount>0){
        mainMonitor = allMonitors[0];
    }else{
        mainMonitor = nullptr;
    }
}

void doAtCloseWindow(GLFWwindow* window){
    void* ptr = glfwGetWindowUserPointer(window);
    if(ptr){
        Window* concreteWindow = static_cast<Window*>(ptr);
        delete concreteWindow;
    }
}