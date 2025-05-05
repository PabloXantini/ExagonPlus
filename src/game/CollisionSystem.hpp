#ifndef COLLISION_SYSTEM_HPP
#define COLLISION_SYSTEM_HPP

#include "Player.hpp"
#include "WallObject.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>

class Collision {
    private:
        /*
            Calcular normales para un poligono (Plano XY)
        */
        void pushNormalsTo(std::vector<glm::vec3>& normals, std::vector<glm::vec3>& objcoors){
            size_t objv = objcoors.size();
            for(size_t i = 0; i<objv; i++){
                glm::vec3 edge = objcoors[(i+1)%objv]-objcoors[i];
                glm::vec3 edgeN = glm::normalize(edge);
                glm::vec3 normalXY = glm::vec3(-edge.y, edge.x, edge.z);
                //Lo guarda en un vector de normales
                normals.push_back(normalXY);
            }
        }
        /*
            Implementacion del Separating Axis Theorem (Para colision de poligonos) para el plano XY
        */
        bool applySAT(std::vector<glm::vec3>& objcoors1, std::vector<glm::vec3>& objcoors2){
            //Local
            std::vector<glm::vec3> normals = {};
            float min1 = INFINITY;
            float max1 = -INFINITY;
            float min2 = INFINITY;
            float max2 = -INFINITY;
            //Saca las normales de cada arista de obj1
            pushNormalsTo(normals, objcoors1);
            //Saca las normales de cada arista de obj2
            pushNormalsTo(normals, objcoors2);
            //SAT
            for(const auto& axis : normals){
                min1 = INFINITY;
                max1 = -INFINITY;
                min2 = INFINITY;
                max2 = -INFINITY;
                for (const auto& v1 : objcoors1){
                    float projection = glm::dot(v1, axis);
                    min1 = std::min(min1, projection);
                    max1 = std::max(max1, projection);
                }
                for (const auto& v2 : objcoors2){
                    float projection = glm::dot(v2, axis);
                    min2 = std::min(min2, projection);
                    max2 = std::max(max2, projection);
                }
                if((min1<max2&&min1>min2)||(min2<max1&&min2>min1)){
                    continue;
                }else{
                    return false;
                }
            }
            return true;
        }
    public:
        Collision()=default;
        /*
            Bandera que determina el estado de colisiones para alguno de los dos tipos de objetos
        */
        bool checkCollision(Player& player, Wall& Wall){
            return applySAT(player.getPos(), Wall.getPos());
        }
        /*
            Metodo principal para realizar las colisiones globales entre jugador y paredes
        */
        void doCollisions(Player& player, std::vector<std::unique_ptr<CompleteWall>>& cWalls){
            //Comprueba si para una pared completa (cada pared) esta cerca step>=0.8
            for(auto& cWall : cWalls){
                for(auto& Wall : cWall->getWalls()){
                    if(Wall.getProgress()>=0.8f){
                        //Checa por SAT
                        if(checkCollision(player, Wall)){
                            std::cout<<"GameOver"<<std::endl;
                        }else{
                            std::cout<<"no"<<std::endl;
                        }
                    }
                }
            }
        }  
};

#endif