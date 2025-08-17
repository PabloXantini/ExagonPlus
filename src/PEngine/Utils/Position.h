#pragma once
#ifndef POSITION_H
#define POSITION_H

struct Vec3f {
    float X;
    float Y;
    float Z;
    Vec3f operator+(const Vec3f& other){
        return {X + other.X, Y + other.Y, Z + other.Z};
    }
    Vec3f operator-(const Vec3f& other){
        return {X - other.X, Y - other.Y, Z - other.Z};
    }
    Vec3f& operator+=(const Vec3f& other){
        X+=other.X;
        Y+=other.Y;
        Z+=other.Z;
        return *this;
    }
};

struct Vec2f {
    float X;
    float Y;
};

#endif