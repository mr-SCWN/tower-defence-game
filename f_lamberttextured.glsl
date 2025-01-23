#version 330


uniform sampler2D tex;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

//Zmienne interpolowane
in float i_nl;
in vec2 i_tc;
in float i_nl2;

void main(void) {
    vec4 color=texture(tex,i_tc);

        // UZYWANIE PIERWSZEGO ZRODLA SWIATLA
//  pixelColor= vec4(color.rgb*i_nl,color.a) ;

        // UZYWANIE DRUGIEGO ZRODLA SWIATLA
//  pixelColor= vec4(color.rgb*i_nl2,color.a);

        // UZYWANIE DWOCH ZRODEL SWIATLA RAZEM
	pixelColor= 0.75 * vec4(color.rgb*i_nl,color.a) + 0.75 * vec4(color.rgb*i_nl2,color.a);

}
