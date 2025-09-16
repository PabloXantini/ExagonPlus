#include "ExagonPlusApp.hpp"

ExagonPlus::ExagonPlus(){}
ExagonPlus::~ExagonPlus(){
    std::cout<<"Game: Goodbye"<<std::endl;
}
void ExagonPlus::execute(){
    PEngine engine;
    engine.init();

    //Game game(&engine);
    //game.init();
    //game.run();
}
