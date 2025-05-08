#ifndef COLLISION_SYSTEM_HPP
#define COLLISION_SYSTEM_HPP

#include "Player.hpp"
#include "WallObject.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>

struct Collision {
    bool collide = false;               //Hubo colision
    glm::vec3 mtv = glm::vec3(0.0f);    //Minimum Translation Vector

    float overlap = 0.0f;               //Solapamiento
    glm::vec3 axis = glm::vec3(0.0f);   //Eje donde ocurre la colision
};

class CollisionSystem {
    private:
        /*
            Calcular la longitud de un solapamiento
        */
        float calculateOverlap(float min1, float max1, float min2, float max2){
            //Corrige localmente para el calculo
            if (min1 > max1) std::swap(min1, max1);
            if (min2 > max2) std::swap(min2, max2);
            //Proteccion
            if (max1 <= min2 || max2 <= min1) return 0.0f;
            //Calcula el solapamiento
            float minOverlap = std::min(min1,min2);
            float maxOverlap = std::max(max1,max2);
            return maxOverlap - minOverlap;
        } 
        /*
            Calcular normales para un poligono (Plano XY)
        */
        void pushNormalsTo(std::vector<glm::vec3>& normals, std::vector<glm::vec3>& objcoors){
            size_t objv = objcoors.size();
            for(size_t i = 0; i<objv; i++){
                glm::vec3 edge = objcoors[(i+1)%objv]-objcoors[i];
                glm::vec3 edgeN = glm::normalize(edge);
                glm::vec3 normalXY = glm::vec3(-edgeN.y, edgeN.x, edgeN.z);
                //Lo guarda en un vector de normales
                normals.push_back(normalXY);
            }
        }
        /*
            Implementacion del Separating Axis Theorem (Para colision de poligonos) para el plano XY
        */
        Collision applySAT(std::vector<glm::vec3>& objcoors1, std::vector<glm::vec3>& objcoors2){
            //Return
            Collision collision;
            float minoverlap = INFINITY;
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
                    float overlap = calculateOverlap(min1, max1, min2, max2);
                    if(overlap<minoverlap){
                        minoverlap=overlap;
                        collision.axis=axis;
                    }
                    continue;
                }else{
                    return collision;
                }
            }
            collision.collide = true;
            collision.overlap = minoverlap;
            collision.mtv = minoverlap*collision.axis;  //The MTV
            return collision;
        }
    public:
        CollisionSystem()=default;
        /*
            Bandera que determina el estado de colisiones para alguno de los dos tipos de objetos
        */
        Collision checkCollision(Player& player, Wall& Wall){
            return applySAT(player.getPos(), Wall.getPos());
        }
        /*
            Resolver la colision
        */
        void resolveCollision(glm::vec3 force){
            //Implementacion de la resolucion de colisiones
            if (fabs(force.y) > fabs(force.x)) {
                if (force.y > 0.5f) {
                    // Colisión por debajo del jugador (el piso)
                    std::cout<<"la colision ocurrio por debajo"<<std::endl;
                } else{
                    std::cout<<"la colision ocurrio por arriba"<<std::endl;
                }
            } else {
                if (force.x > 0.5f) {
                    // Colisión desde la izquierda
                    std::cout<<"la colision ocurrio por la izquierda"<<std::endl;
                } else {
                    // Colisión desde la derecha
                    std::cout<<"la colision ocurrio por la derecha"<<std::endl;
                }
            }
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
                        Collision collision;
                        collision = checkCollision(player, Wall);
                        if(collision.collide){
                            std::cout<<"Hubo Colision"<<std::endl;
                            std::cout<<collision.overlap<<std::endl;
                            printVec3(collision.axis);
                            printVec3(collision.mtv);
                            resolveCollision(collision.axis);
                            //De momento cualquier colision es GAMEOVER
                            player.setLiveStatus(false);
                        }
                    }
                }
            }
        }  
};

#endif