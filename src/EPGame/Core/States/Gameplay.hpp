#ifndef EXAGON_PLUS_GAMEPLAY_HPP
#define EXAGON_PLUS_GAMEPLAY_HPP

#include "../GameState.hpp"

class Game;
class Model;
class GameObject3D;

class GamePlay : public GameState {
    private:
        //Renderer* simpleRenderer;
        //UNA CLASE
        //Su referencia
        Model* model;
        //El objeto en cuestion
        GameObject3D* rectangle;
        //std::unique_ptr<Mesh<WVertex3D>> testMesh;
        //Transform3D* t;
        //Variables de un objeto custom (ajeno a Object Engine)
        float ROTZ = 0.0f;
        float TX = 0.0f;
        float SPEEDZ = 30.0f;
        float SPEEDTX = 0.5f;
    public:
        GamePlay(PEngine* engine);
        ~GamePlay();
        void init() override;
        void show() override;
        void update(float dT) override;
};

#endif