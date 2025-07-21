#ifndef G_CORE_HPP
#define G_CORE_HPP

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
        IGCore(): 
            bufferManager(bufferManager)
        {};
        virtual ~IGCore(){};
        IBufferManager* allocate(){
            return bufferManager;
        };
};

#endif