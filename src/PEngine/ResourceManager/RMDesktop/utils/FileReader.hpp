#pragma once
#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include <sstream>
#include <fstream>

std::string readFile(const char* filePath){
    std::string info;
    std::ifstream file;
    //Excepciones
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    //Abre el archivo
    file.open(filePath);
    std::stringstream stream;
    //Lo lee por partes
    stream << file.rdbuf();
    //Lo cierra
    file.close();
    //Guarda la informacion
    info = stream.str();
    return info;
}

#endif