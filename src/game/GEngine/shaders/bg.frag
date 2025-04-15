#version 330 core
// Recibido desde bg.vert
in vec3 oFragColor; 

out vec4 FragColor;

void main() {
    // Color final del fragmento
    FragColor = vec4(oFragColor, 1.0f); 
}