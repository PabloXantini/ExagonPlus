#ifndef SCENE_HPP
#define SCENE_HPP

class Scene {
    public:
        Scene() = default;
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