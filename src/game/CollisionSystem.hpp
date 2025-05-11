#ifndef COLLISION_SYSTEM_HPP
#define COLLISION_SYSTEM_HPP

#include "Player.hpp"
#include "WallObject.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>

//Diferencia el propietario de la normal
enum ObjOwner {
    UNKNOWN,
    OBJ1,
    OBJ2
};
//Etiquetado de lados
enum Side {
    NONE, S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10
};
//El eje de colision de un objeto objetivo
struct Axis {
    ObjOwner owner = UNKNOWN;           //Origen
    Side sidename = NONE;               //Lado
    glm::vec3 axis = glm::vec3(0.0f);   //Eje donde ocurre la colision
};
//Informacion general de la colision
struct Collision {
    //General
    bool collide = false;               //Hubo colision
    glm::vec3 mtv = glm::vec3(0.0f);    //Minimum Translation Vector
    float overlap = 0.0f;               //Solapamiento
    glm::vec3 axis = glm::vec3(0.0f);   //Eje donde ocurre la colision
    //ObjTarget
    Side collidedside = NONE;           //Lado colisionado del objetivo
};

class CollisionSystem {
    private:
        /*
            Imprime un lado de la colision
        */
        std::string showSide(Side side){
            switch (side) {
                case NONE: return "NONE";
                case S0: return "S0";
                case S1: return "S1";
                case S2: return "S2";
                case S3: return "S3";
                case S4: return "S4";
                case S5: return "S5";
                case S6: return "S6";
                case S7: return "S7";
                case S8: return "S8";
                case S9: return "S9";
                case S10: return "S10";
                default: return "INVALIDO";
            }
        }
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
            float minOverlap = std::max(min1,min2);
            float maxOverlap = std::min(max1,max2);
            return maxOverlap - minOverlap;
        } 
        /*
            Calcular normales para un poligono (Plano XY)
        */
        void pushNormalsTo(std::vector<Axis>& normals, std::vector<glm::vec3>& objcoors, ObjOwner owner){
            Axis normal;
            size_t objv = objcoors.size();
            for(size_t i = 0; i<objv; i++){
                glm::vec3 edge = objcoors[(i+1)%objv]-objcoors[i];
                glm::vec3 edgeN = glm::normalize(edge);
                glm::vec3 normalXY = glm::vec3(-edgeN.y, edgeN.x, edgeN.z);
                //Lo guarda en un vector de normales
                normal.owner = owner;
                normal.axis = normalXY;
                normal.sidename = static_cast<Side>(i+1);
                normals.push_back(normal);
            }
        }
        /*
            Implementacion del Separating Axis Theorem (Para colision de poligonos) para el plano XY
        */
        Collision applySAT(std::vector<glm::vec3>& objcoors1, std::vector<glm::vec3>& objcoors2, ObjOwner target){
            //Return
            Collision collision;
            float minoverlap = INFINITY;
            //Local
            std::vector<Axis> normals = {};
            float min1 = INFINITY;
            float max1 = -INFINITY;
            float min2 = INFINITY;
            float max2 = -INFINITY;
            //Saca las normales de cada arista de obj1
            pushNormalsTo(normals, objcoors1, ObjOwner::OBJ1);
            //Saca las normales de cada arista de obj2
            pushNormalsTo(normals, objcoors2, ObjOwner::OBJ2);
            //SAT
            for(const auto& normal : normals){
                min1 = INFINITY;
                max1 = -INFINITY;
                min2 = INFINITY;
                max2 = -INFINITY;
                for (const auto& v1 : objcoors1){
                    float projection = glm::dot(v1, normal.axis);
                    min1 = std::min(min1, projection);
                    max1 = std::max(max1, projection);
                }
                for (const auto& v2 : objcoors2){
                    float projection = glm::dot(v2, normal.axis);
                    min2 = std::min(min2, projection);
                    max2 = std::max(max2, projection);
                }
                if((min1<max2&&min1>min2)||(min2<max1&&min2>min1)){
                    float overlap = calculateOverlap(min1, max1, min2, max2);
                    if(overlap<minoverlap){
                        minoverlap=overlap;
                        collision.axis=normal.axis;
                        if(normal.owner!=target) collision.axis=-normal.axis;
                        if(normal.owner==target) collision.collidedside=normal.sidename;
                    }
                }else{
                    return collision;
                }
            }
            collision.collide = true;
            collision.overlap = minoverlap;
            collision.mtv = minoverlap*collision.axis;  //MTV (Minimum Translation Vector)

            return collision;
        }
    public:
        CollisionSystem()=default;
        /*
            Bandera que determina el estado de colisiones para alguno de los dos tipos de objetos
        */
        Collision checkCollision(Player& player, Wall& Wall){
            return applySAT(player.getPos(), Wall.getPos(), ObjOwner::OBJ2);
        }
        /*
            Resolver la colision del jugador
        */
        void resolveCollision(Collision force, Player& player){
            //Implementacion de la resolucion de colisiones
            switch(force.collidedside){
                case Side::NONE: //Lado ajeno
                    player.collide(force.mtv);
                    break;
                case Side::S0:  //Arista inferior
                    //std::cout<<"la colision ocurrio por debajo"<<std::endl;
                    player.setLiveStatus(false);
                    //GAMEOVER
                    break;
                case Side::S1:  //Arista lateral
                    //std::cout<<"la colision ocurrio por un lateral"<<std::endl;
                    player.collide(force.mtv);
                    //Comportamiento solido
                    break;
                case Side::S2:  //Arista superior
                    //std::cout<<"la colision ocurrio por arriba"<<std::endl;
                    break;
                case Side::S3:  //Arista lateral
                    //std::cout<<"la colision ocurrio por un lateral"<<std::endl;
                    player.collide(force.mtv);
                    //Comportamiento solido
                    break;
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
                            //std::cout<<"Hubo Colision"<<std::endl;
                            printVec3(collision.mtv);
                            //printVec3(collision.axis);
                            //std::cout<<collision.overlap<<std::endl;
                            std::cout<<showSide(collision.collidedside)<<std::endl;
                            resolveCollision(collision, player);
                        }
                    }
                }
            }
        }  
};

#endif