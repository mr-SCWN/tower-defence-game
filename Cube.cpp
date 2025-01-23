#include "Cube.h"
#include "shaderprogram.h"
#include <glm/gtc/type_ptr.hpp>

void Cube::drawCube(glm::mat4 P, glm::mat4 V, glm::mat4 M){
	spColored->use(); //Aktywuj program cieniujący

	glUniformMatrix4fv(spColored->u("P"), 1, false, glm::value_ptr(P)); //Załaduj do programu cieniującego macierz rzutowania
	glUniformMatrix4fv(spColored->u("V"), 1, false, glm::value_ptr(V)); //Załaduj do programu cieniującego macierz widoku
	glUniformMatrix4fv(spColored->u("M"), 1, false, glm::value_ptr(M)); //Załaduj do programu cieniującego macierz modelu


	glEnableVertexAttribArray(spColored->a("vertex"));
	glVertexAttribPointer(spColored->a("vertex"), 4, GL_FLOAT, false, 0, myCubeVertices); //Współrzędne wierzchołków bierz z tablicy birdVertices

	glEnableVertexAttribArray(spColored->a("color"));
	glVertexAttribPointer(spColored->a("color"), 4, GL_FLOAT, false, 0, myCubeColors); //Współrzędne wierzchołków bierz z tablicy birdColors

	glDrawArrays(GL_TRIANGLES, 0, myCubeVertexCount);

	glDisableVertexAttribArray(spColored->a("vertex"));
	glDisableVertexAttribArray(spColored->a("color"));

}