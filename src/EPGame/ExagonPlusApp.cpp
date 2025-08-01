#include "ExagonPlusApp.hpp"

ExagonPlus::ExagonPlus(){}
ExagonPlus::~ExagonPlus(){
    std::cout<<"Goodbye"<<std::endl;
}
void ExagonPlus::run(){
    PEngine engine;
    engine.init();
    //engine.getGraphics().allocate()->decirAlgo();
    auto mainWindow = engine.getGraphics().getWinManager()->createWindow(800, 600, "ExagonPlus");
    //engine.getGraphics().getWinManager()->createWindow(1200, 800, "ExagonPlus Ventana Secundaria");
    
    engine.getResourceManager().processShader()->loadShader("background", {{ShaderPart::VERTEX, "EPGame/shaders/bg.vert"},{ShaderPart::FRAGMENT, "EPGame/shaders/bg.frag"}});
    
    //ULTIMO METODO QUE VOY A EJECUTAR
    engine.getGraphics().getWinManager()->runAsOnlyWindow(mainWindow);
    //engine.getGraphics().getWinManager()->runAsVariousWindows(mainWindow);
}
