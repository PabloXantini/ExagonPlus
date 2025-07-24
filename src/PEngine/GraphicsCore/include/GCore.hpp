#ifndef G_CORE_HPP
#define G_CORE_HPP

#include "../Desktop/WindowManager.hpp"

#include <iostream>

class IBufferManager {
    public:
        IBufferManager() = default;
        virtual ~IBufferManager(){}
        virtual void decirAlgo() = 0;
};

class IGCore {
    protected:
        IBufferManager* bufferManager; 
    public:
        IGCore(){};
        virtual ~IGCore(){};
        virtual WindowManager* getWinManager(){
            return nullptr;
        }
        IBufferManager* allocate(){
            return bufferManager;
        };
};

#endif