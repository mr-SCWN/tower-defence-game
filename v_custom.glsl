#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 normal; //wektor normalny w wierzcholku
in vec2 texCoord; //wspórzędne teksturowania


void main(void) {
    gl_Position=P*V*M*vertex;
}
