#ifndef EXAGON_GAME_PROCESS_HPP
#define EXAGON_GAME_PROCESS_HPP

#include "BG.hpp"

#include <iostream>

class ExagonGameProcess {
    private:
        BG bg;
    public:
        //Constructor
        ExagonGameProcess()=default;
        //Getters   
        const BG& getBG() const {
            return bg;
        }
        //Setters
        void setBG(BG tobg){
            bg=tobg;
        }
};

#endif