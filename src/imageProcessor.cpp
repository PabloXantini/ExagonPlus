#include "../include/FreeImage/FreeImage.h"

#include <iostream>

void processImage(FIBITMAP* bitmap);

unsigned char* loadImage(const char* filename_path, int& width, int& height) {
    FreeImage_Initialise();

    // Cargar imagen desde la ruta especificada
    FIBITMAP* bitmap = FreeImage_Load(FIF_PNG, filename_path, PNG_DEFAULT);
    if (!bitmap) {
        std::cerr << "Error al cargar la imagen: " << filename_path << std::endl;
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

