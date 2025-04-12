#include <windows.h>
#include <filesystem>

#include "../include/FreeImage/FreeImage.h"

#include "resource.h"

#include <iostream>

//Carga una imagen incrustado en memoria
FIBITMAP* loadImageFromResource(int resourceID) {
    HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(resourceID), RT_RCDATA);
    if (!hResource) return nullptr;

    HGLOBAL hResData = LoadResource(NULL, hResource);
    if (!hResData) return nullptr;

    void* pData = LockResource(hResData);
    DWORD size = SizeofResource(NULL, hResource);
    
    // Crea un stream de FreeImage desde memoria
    FIMEMORY* stream = FreeImage_OpenMemory((BYTE*)pData, size);
    FREE_IMAGE_FORMAT format = FreeImage_GetFileTypeFromMemory(stream);
    FIBITMAP* dib = FreeImage_LoadFromMemory(format, stream);
    
    FreeImage_CloseMemory(stream);
    return dib;
}
  
//Corregir el color de la imagen
void processImage(FIBITMAP* bitmap) {
    int width = FreeImage_GetWidth(bitmap);
    int height = FreeImage_GetHeight(bitmap);
    BYTE* bits = FreeImage_GetBits(bitmap);
   
    int pitch = FreeImage_GetPitch(bitmap);
   
    for (int y = 0; y < height; y++) {
        BYTE* pixel = bits + y * pitch;  // Línea de la imagen
        for (int x = 0; x < width; x++) {
             // Intercambiar BGR -> RGB
            std::swap(pixel[0], pixel[2]);
            pixel += 4;  // Siguiente pixel (asumiendo 32 bits)
        }
    }
}
   
//=========================================================DEBUGGING===================================================================
//Metodos relacionados a la depuracion de archivos
void showAbsolutePath(const std::string& ruta) {
    std::filesystem::path p = std::filesystem::absolute(ruta);
    std::cout << "[DEBUG] Ruta absoluta: " << p << std::endl;
}

//Metodo importante
unsigned char* loadImage(int resID, int &width, int &height) {
    FreeImage_Initialise();
    // Obtiene el bitmap de la imagen desde el recurso
    FIBITMAP* bitmap = loadImageFromResource(resID);
    if (!bitmap) {
        std::cerr << "No se pudo cargar el recurso con ID: " << resID << std::endl;
        FreeImage_DeInitialise();
        return nullptr;
    }
    // Convertir la imagen a formato 32 bits (RGBA)
    FIBITMAP* bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
    FreeImage_Unload(bitmap);
    
    // Procesar imagen
    processImage(bitmap32);

    // Obtener el largo y ancho de los pixeles 
    width = FreeImage_GetWidth(bitmap32);
    height = FreeImage_GetHeight(bitmap32);

    // Se invierte la imagen horizontalmente
    FreeImage_FlipVertical(bitmap32);
    
    // Obtener datos de los píxeles
    unsigned char* pixels = new unsigned char[width * height * 4]; // 4 bytes por píxel (RGBA)
    memcpy(pixels, FreeImage_GetBits(bitmap32), width * height * 4);

    FreeImage_Unload(bitmap32);
    FreeImage_DeInitialise();

    return pixels;
}

