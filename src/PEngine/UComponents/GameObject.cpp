#include "GameObject.hpp"
#include "../PEngineMain.hpp"

GameObject::GameObject(PEngine* EngineContext) : context(EngineContext) {}

void GameObject::attachModel(Model* model){
     this->model = model;
}

void GameObject::draw(){
    if(model) renderer->draw(model);
}

GameObject2D::GameObject2D(PEngine* EngineContext, Renderer* renderer):
    GameObject(EngineContext)
{
    this->renderer = renderer;
}

GameObject2D::~GameObject2D(){

}

GameObject3D::GameObject3D(PEngine* EngineContext, Renderer* renderer):
    GameObject(EngineContext)
{
    //Snippets
    auto& graphics = EngineContext->getGraphics();
    //Constructs 
    this->renderer = renderer;
    this->model = graphics.model()->createModel();
    this->transform = graphics.getTransform()->useTransform3D();
}

GameObject3D::~GameObject3D(){
    delete model;
    delete transform;
}