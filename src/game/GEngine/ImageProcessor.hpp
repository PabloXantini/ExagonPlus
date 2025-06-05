#ifndef IMAGE_PROCESSOR_HPP
#define IMAGE_PROCESSOR_HPP

#include <windows.h>
#include <filesystem>

#include <FreeImage/FreeImage.h>

#include "../../resource.h"

#include <iostream>

//=========================================================SECUNDARIOS============================================================
//Carga una imagen incrustado en memoria
FIBITMAP* loadImageFromResource(int resourceID);
//Corregir el color de la imagen
void processImage(FIBITMAP* bitmap);
//=========================================================DEBUGGING==============================================================
//Metodos relacionados a la depuracion de archivos
void showAbsolutePath(const std::string& ruta);
//=========================================================MAIN===================================================================
//METODOS PRINCIPALES
unsigned char* loadImage(int resID, int &width, int &height);

#endif
