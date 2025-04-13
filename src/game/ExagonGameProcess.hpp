#ifndef EXAGON_GAME_PROCESS_HPP
#define EXAGON_GAME_PROCESS_HPP

#include "BG.hpp"

class ExagonGameProcess {
    private:
        BG bg;
    public:
        //Constructor
        ExagonGameProcess();
        //Getters   
        const BG& getBG() const {
            return bg;
        }
        //Setters
        void setBG(BG tobg){
            bg=tobg;
        }
};

ExagonGameProcess::ExagonGameProcess():
    bg(1.2f,7)
    {

    }

#endif