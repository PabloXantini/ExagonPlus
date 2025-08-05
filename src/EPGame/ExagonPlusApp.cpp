#include "ExagonPlusApp.hpp"

ExagonPlus::ExagonPlus(){}
ExagonPlus::~ExagonPlus(){
    std::cout<<"Goodbye"<<std::endl;
}
void ExagonPlus::run(){
    PEngine engine;
    engine.init();

    //Window setup
    auto mainWindow = engine.getGraphics().getWinManager()->createWindow(800, 600, "ExagonPlus");
    //engine.getGraphics().getWinManager()->createWindow(1200, 800, "ExagonPlus Ventana Secundaria");

    //Scene Setup
    RenderTest test(&engine);
    test.init();

    mainWindow->setScene(&test);

    //ULTIMO METODO QUE VOY A EJECUTAR
    engine.getGraphics().getWinManager()->runAsOnlyWindow(mainWindow);
    //engine.getGraphics().getWinManager()->runAsVariousWindows(mainWindow);
}
