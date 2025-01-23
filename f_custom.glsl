#version 330


out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

// in vec4 i_c;
uniform vec4 color=vec4(0.2,0.5,0.3,1);

void main(void) {
	pixelColor=color;
}
