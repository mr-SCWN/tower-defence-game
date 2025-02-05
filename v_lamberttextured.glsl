#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


uniform vec4 lightDir=vec4(1,1,1,0); // PIERWSZE ZRODLO SWIATLA

uniform vec4 lightDir2=vec4(0,0,1,0); // DRUGIE ZRODLO SWIATLA

//Atrybuty
layout (location=0) in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location=1) in vec4 normal; //wektor normalny w wierzcholku
layout (location=2) in vec2 texCoord; //wsp�rz�dne teksturowania


//Zmienne interpolowane
out vec2 i_tc;
out float i_nl;
out float i_nl2;

void main(void) {
    gl_Position=P*V*M*vertex;

    mat4 G=mat4(inverse(transpose(mat3(M))));
    vec4 n=normalize(V*G*normal);

    i_nl=clamp(dot(n,lightDir),0,1);
    i_nl2=clamp(dot(n,lightDir2),0,1);

    i_tc=texCoord;
}
