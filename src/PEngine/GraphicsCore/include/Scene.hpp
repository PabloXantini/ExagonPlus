#ifndef SCENE_HPP
#define SCENE_HPP

class Scene {
    public:
        Scene() = default;
        virtual void show(){}
        virtual void update(float deltaTime){}
};

#endif