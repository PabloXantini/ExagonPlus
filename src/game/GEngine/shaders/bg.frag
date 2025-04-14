#version 330 core
// Recibido desde bg.vert
in vec3 FragColor; 

out vec4 FragColor;

void main() {
    // Color final del fragmento
    FragColor = vec4(FragColor, 1.0f); 
}