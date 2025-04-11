#include "../include/GLFW/glfw3.h"

#include <stdio.h>

#include "ExagonGameProcess.cpp"
#include "Engine.cpp"

Engine engine;

int LoadEngine(){
    unsigned int shaders;
    shaders=engine.initEngine();
    return shaders;  
}

void Clear(int shaders){
    engine.clearBuffers(shaders);
}

void PaintGame(int shaders){
    glUseProgram(shaders);
    glBindVertexArray(engine.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //printf("Este es un modulo importado de C\n");    
}