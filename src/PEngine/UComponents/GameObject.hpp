#pragma once
#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

class PEngine;
class Model;
class Renderer;
class Transform3D;

class GameObject {
    private:
        PEngine* context;
    protected:
        Model* model = nullptr;
        Renderer* renderer;
    public:
        GameObject(PEngine* EngineContext);
        virtual ~GameObject() = default;
        Model* getModel(){
            return this->model;
        }
        void attachModel(Model* model);
        void draw();
};

class GameObject2D : public GameObject {
    private:
        //Transform2D* transform;
    public:
        GameObject2D(PEngine* EngineContext, Renderer* renderer = nullptr);
        ~GameObject2D();
};

class GameObject3D : public GameObject {
    private:
        Transform3D* transform;
    public:
        GameObject3D(PEngine* EngineContext, Renderer* renderer = nullptr);
        ~GameObject3D();
        Transform3D* getTransform(){
            return this->transform;
        }
};

#endif