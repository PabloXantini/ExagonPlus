#version 330 core
// Recibido desde bg.vert
in vec3 oFragColor; //Color original del vertice

out vec4 FragColor; //Color de salida

// Variables de set del shader
uniform float uTime;
uniform float HueFactor;
uniform float HueSpeed;

// Función RGB a HSV
vec3 rgb2hsv(vec3 c) {
    float cMax = max(c.r, max(c.g, c.b));
    float cMin = min(c.r, min(c.g, c.b));
    float delta = cMax - cMin;

    float h = 0.0;
    if (delta > 0.00001) {
        if (cMax == c.r) {
            h = mod((c.g - c.b) / delta, 6.0);
        } else if (cMax == c.g) {
            h = ((c.b - c.r) / delta) + 2.0;
        } else {
            h = ((c.r - c.g) / delta) + 4.0;
        }
        h *= 60.0;
        if (h < 0.0) h += 360.0;
    }

    float s = (cMax == 0.0) ? 0.0 : (delta / cMax);
    float v = cMax;

    return vec3(h, s, v);
}

// Función HSV a RGB
vec3 hsv2rgb(vec3 c) {
    float h = c.x;
    float s = c.y;
    float v = c.z;

    float c1 = v * s;
    float x = c1 * (1.0 - abs(mod(h / 60.0, 2.0) - 1.0));
    float m = v - c1;

    vec3 rgb;

    if (h < 60.0) rgb = vec3(c1, x, 0);
    else if (h < 120.0) rgb = vec3(x, c1, 0);
    else if (h < 180.0) rgb = vec3(0, c1, x);
    else if (h < 240.0) rgb = vec3(0, x, c1);
    else if (h < 300.0) rgb = vec3(x, 0, c1);
    else rgb = vec3(c1, 0, x);

    return rgb + vec3(m);
}

void main() {
    //Convierto en HSV temporalmente
    vec3 hsv = rgb2hsv(oFragColor);
    //Aplico la distancia de desplazamiento del HUE
    float HueOffset = 180.0 * HueFactor;
    //Le sumo al HUE
    hsv.x += HueOffset*sin(uTime * HueSpeed);
    //Chequeo por si se pasa HUE de 360
    if(hsv.x>360.0){
        float rest = hsv.x - 360.0;
        hsv.x=rest;
    }
    //Chequeo por si se pasa HUE de 0
    if(hsv.x<0.0){
        float rest = 360.0 + hsv.x;
        hsv.x=rest;
    }
    FragColor = vec4(hsv2rgb(hsv), 1.0);
}