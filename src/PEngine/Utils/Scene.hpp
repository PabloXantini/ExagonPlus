#ifndef SCENE_HPP
#define SCENE_HPP

/*
    This class waits an implementation of the PEngine
*/
class PEngine;

/*
    This class is the pipeline for your application
*/
class Scene {
    protected:
        PEngine* context;
    public:
        Scene(PEngine* engineContext): context(engineContext){};
        /*
            Implement this function for load your elements in this scene
        */
        virtual void init(){}
        /*
            Implement this function for show elements on the main or specified window
        */
        virtual void show(){}
        /**
         * Implement this function for your game logic
         * @param dT is the current value of delta-Time 
         */
        virtual void update(float dT){}
};

#endif