#ifndef EXAGON_GAME_PROCESS_HPP
#define EXAGON_GAME_PROCESS_HPP

#include "BG.hpp"

class ExagonGameProcess {
public:
    ExagonGameProcess();
    const BG& getBG() const;
private:
    BG bg;
};

ExagonGameProcess::ExagonGameProcess() {}

//Getters
const BG& ExagonGameProcess::getBG() const {
    return bg;
}

#endif