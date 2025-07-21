#include "PEngine/PEngineMain.hpp"
#include <iostream>

int main(){
    printf("Me ejecuto\n");
    PEngine engine;
    engine.init();
    engine.getGraphics().allocate()->decirAlgo();
    return 0;
};