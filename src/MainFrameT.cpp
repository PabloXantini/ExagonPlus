#include "PEngine/PEngineMain.hpp"
#include <iostream>

int main(){
    printf("Me ejecuto\n");
    PEngine engine;
    engine.init();
    //engine.getGraphics().allocate()->decirAlgo();
    auto mainWindow = engine.getGraphics().getWinManager()->createWindow(800, 600, "ExagonPlus");
    //engine.getGraphics().getWinManager()->createWindow(1200, 800, "ExagonPlus Ventana Secundaria");
    engine.getGraphics().getWinManager()->runAsOnlyWindow(mainWindow);
    //engine.getGraphics().getWinManager()->runAsVariousWindows(mainWindow);
    return 0;
};