#include "WindowManager.hpp"

WindowManager::WindowManager(Time* time): time(time){
    renderer = new SceneRenderer();
}
WindowManager::~WindowManager(){
    delete renderer;
}

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
    WindowResolution res;
    res.width = width;
    res.height = height;
    if(fullscreen){
        checkMonitors();
        if (monitorIndex > 0 && monitorIndex <= (unsigned int)(monitorCount)){
            monitorSelected = allMonitors[monitorIndex-1];
            const GLFWvidmode* mode = glfwGetVideoMode(monitorSelected);
            res.currentWidth = mode->width;
            res.currentHeight = mode->height;
        }
    }else{
        res.currentWidth = width;
        res.currentHeight = height;
    }
    //Genera una ventana
    newWindow = new Window(renderer, res, title, monitorSelected, windowShared);

    /*
    if(!GLADLinked){
        GLADLinked = linkGLAD();
        if(!GLADLinked) {
            delete newWindow;
            return nullptr;
        }
    }
    */
    //*
    if(!linkGLAD()) {
        delete newWindow;
        return nullptr;
    }
    //*/
    windows.push_back(newWindow);
    return newWindow;

}

void WindowManager::runAsOnlyWindow(Window* mainWindow){
    setGLconfig(mainWindow);
    glfwSwapInterval(1);
    while(!mainWindow->isShouldClose()){
        time->check();
        renderInWindow();
        mainWindow->render(time);
        //std::cout<<time->getDeltaTime()<<"\n";
        glfwPollEvents();
    }
    delete mainWindow;
    glfwTerminate();
}

void WindowManager::runAsVariousWindows(Window* mainWindow){
    //De momento voy a poner esto
    glfwSwapInterval(1);
    while(!mainWindow->isShouldClose()){
        time->check();
        for(auto window = windows.begin(); window != windows.end();){
            glfwMakeContextCurrent((*window)->getWindowReference());
            setGLconfig(*window);
            renderInWindow();
            (*window)->render(time);
            std::cout<<time->getDeltaTime()<<"\n";
            if((*window)->isShouldClose()){
                delete *window;
                window = windows.erase(window);
                time->sync();
            }else{
                ++window;
            }
        }
        glfwPollEvents();
    }
    for (auto window = windows.begin(); window != windows.end();){
        (*window)->close();
        delete *window;
        window = windows.erase(window);
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
        std::cout<<concreteWindow->getWidth()<<std::endl;
        concreteWindow->markAsClosed(true);
    }
}