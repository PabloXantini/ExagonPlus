#ifndef VERTEX_H
#define VERTEX_H
#define MAX_BONE_INFUENCE 32

#include "Position.h"
#include "Color.h"

struct WVertex3D{
    Vec3f position;
    DecRGB color;
};

struct Vertex3D{
    Vec3f position;
    Vec3f normals;
    Vec2f textCoor;
    Vec3f tangent;
    Vec3f bitTangent;
    int BoneIDs[MAX_BONE_INFUENCE];
    float Weights[MAX_BONE_INFUENCE];
};

#endif