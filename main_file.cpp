#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "default_tower.h"
#include "shaderprogram.h"
#include "Player.h"
#include <vector>
#include "Terrain.h"
#include "Cursor.h"
#include "Enemy.h"
#include "FlyingEnemy.h"
#include "Tower.h"
#include "lodepng.h"
#include "Functions.h"
#include "Base.h"
#include "light.h"
#include "Boom.h"

void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

glm::mat4 M;
glm::mat4 V;
glm::mat4 P;

glm::vec3 basePosition(10.0f,Functions::getHeight(10.0f,10.0f,0.2f),10.0f);
//float xxx = 2.0f;
//glm::vec3 boomPosition(xxx,Functions::getHeight(2.0f,14.0f,0.2f),14.0f);
//glm::vec3 basePosition(5.0f,10.0f,14.0f);
//bool died = false;

light* general_light ;

Player player;
vector<Enemy> enemies;
vector<FlyingEnemy> flying_enemies;
vector<Tower> towers;
Terrain terrain;
Cursor cursorMesh;
Base baseMesh;
Boom explores;
//vector<Boom> explores;

//tekstury
GLuint stones;
GLuint bricks;
GLuint metal;
GLuint color_for_enemy;
GLuint color_for_flyenemy;
GLuint color_cursor;
GLuint color_of_explore;

void addTower(){
    if(player.cash>0 && glm::length(player.cursor - basePosition) > 1.0f){
        default_tower newTower;
        newTower.setTexture(metal);
        newTower.setPosition(player.cursor);
        newTower.setBasePosition(basePosition);
        towers.push_back(newTower);
        player.cash--;
    }
}

void addEnemy(){
    bool isFlying = rand()%10>5;
    if(isFlying){
        FlyingEnemy newEnemy;
        newEnemy.setTexture(color_for_flyenemy);
        newEnemy.setTargetPosition(basePosition);
        newEnemy.spawn();
        flying_enemies.push_back(newEnemy);
    }
    else{
        Enemy newEnemy;
        newEnemy.setTexture(color_for_enemy);
        newEnemy.setTargetPosition(basePosition);
        newEnemy.spawn();
        enemies.push_back(newEnemy);
    }

}
/*
void addBoom(){
    Boom newBoom;
    newBoom.setTexture(color_of_explore);
    newBoom.setTargetPosition(basePosition);
    newBoom.spawn();
    explores.push_back(newBoom);
}
*/


void displayTowers(){
    for(auto tower: towers){
        glm::mat4 Mt = glm::translate(M, tower.getPosition());
        Mt = glm::rotate(Mt, tower.getRotation(), glm::vec3(0,1.0f,0));
        Mt = glm::scale(Mt, glm::vec3(0.1f,0.2f,0.1f));
        tower.draw(P, V, Mt);
    }
}

void displayEnemies(){
    for(auto enemy: enemies){
        glm::mat4 Mt = glm::translate(M, enemy.getPosition());
        Mt = glm::rotate(Mt, enemy.getRotation(), glm::vec3(0,1.0f,0));
        Mt = glm::rotate(Mt, enemy.getRotationX(),glm::vec3(1.0f,0,0) );
        Mt = glm::scale(Mt, glm::vec3(0.1f,0.1f,0.1f));
        enemy.draw(P, V, Mt);


       //  Mt = glm::scale(Mt, glm::vec3(3.0f,3.0f,3.0f));
        //explores.draw(P,V,Mt);
    }

    for(auto enemy: flying_enemies){
        glm::mat4 Mt = glm::translate(M, enemy.getPosition());
        Mt = glm::rotate(Mt, enemy.getRotation(), glm::vec3(0,1.0f,0));
        Mt = glm::scale(Mt, glm::vec3(0.1f,0.1f,0.1f));
        enemy.draw(P, V, Mt);
    }
}




void displayBoom(glm::vec3 boomPosition){

        glm::mat4 Mt = glm::translate(M, boomPosition);
        Mt = glm::scale(Mt, glm::vec3(0.5f,0.5f,0.5f));
        explores.draw(P,V,Mt);
    
}




void displayCursor(){
    glm::mat4 cursor = glm::translate(M, player.cursor);
    cursor = glm::scale(cursor, glm::vec3(0.01f, 0.01f, 0.01f));
    cursorMesh.draw(P, V, cursor);
}

void displayBase(){
    glm::mat4 base = glm::translate(M, basePosition);
    base = glm::scale(base, glm::vec3(0.2f, 0.2f, 0.2f));
    baseMesh.draw(P, V, base);
}




void enemiesMove(double interval){
    for(auto &enemy: enemies){
        enemy.move(interval);
        if(glm::length(enemy.getPosition() - basePosition) < 0.2f){
            enemy.attack();
            player.hp--;
        }
            
    }
    for(auto &enemy: flying_enemies){
        enemy.move(interval);
        if(glm::length(enemy.getPosition() - basePosition) < 1.2f){
            enemy.attack();
            player.hp--;
        }
            
    }
}

void towersShoot(){
    for(auto &tower: towers){
        for(auto &enemy: enemies){

            
            if(glm::length(tower.getPosition() - enemy.getPosition()) < tower.getRange()){
                displayBoom(enemy.getPosition());
                tower.shoot();
                enemy.die();
                //died = true;
                addEnemy();
                player.cash++;
            }
            
        }

        for(auto &enemy: flying_enemies)
            if(glm::length(tower.getPosition() - enemy.getPosition()) < tower.getRange()){
                tower.shoot();
                enemy.die();
                //died = true;
                //displayBoom();
                addEnemy();
                player.cash++;
            }   
    }
}


void restartGame(){
    player.pos = basePosition + glm::vec3(0,0,-2.0f);
    player.cash=3;
    player.hp=3;
    towers.clear();
    enemies.clear();
    flying_enemies.clear();
    addEnemy();
   // addBoom();
}

void lose(GLFWwindow* window){
    while(player.hp<=0){
        printf("you lost, press R to restart\n");
        glfwPollEvents();
        if(glfwWindowShouldClose(window))
            break;
    }
    
    restartGame();
}

int choose_tower = 1;
void key_callback(
    GLFWwindow* window,
    int key,
    int scancode,
    int action,
    int mod
) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_A)
            player.speed.x = 1;
        if (key == GLFW_KEY_D)
            player.speed.x = -1;
        if (key == GLFW_KEY_S)
            player.speed.z = -1;
        if (key == GLFW_KEY_W)
            player.speed.z = 1;

        if (key == GLFW_KEY_SPACE) {
            addTower();
        }
        if (key == GLFW_KEY_Z) {
            addEnemy();
        //    addBoom();
        }
        if (key == GLFW_KEY_R) {
            restartGame();
        }
        if (key == GLFW_KEY_1) {
            choose_tower = 1;
        }
        else if (key == GLFW_KEY_2) {
            choose_tower = 2;
        }
        else if (key == GLFW_KEY_3) {
            choose_tower = 3;
        }
    }
    if (action == GLFW_RELEASE) {
        if (key == GLFW_KEY_A || key == GLFW_KEY_D)
            player.speed.x = 0;
        if (key == GLFW_KEY_S || key == GLFW_KEY_W)
            player.speed.z = 0;
    }
}

//pewnie do dopracowania
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    player.cursor.x = player.pos.x - xpos / 100 + 2.4f;
    player.cursor.z = player.pos.z - ypos / 100 + 7.0f;
}



GLuint readTexture(const char* filename) {
    GLuint temp;
    glActiveTexture(GL_TEXTURE0);

    //Wczytanie do pamięci komputera
    std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
    unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
    //Wczytaj obrazek
    unsigned error = lodepng::decode(image, width, height, filename);

    //Import do pamięci karty graficznej
    glGenTextures(1, &temp); //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, temp); //Uaktywnij uchwyt
    //Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
       GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT);

    return temp;
}


void initOpenGLProgram(GLFWwindow* window) {
    initShaders();
    glClearColor(0.1, 0.8, 0.9, 1);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    stones = readTexture("stones.png");
    bricks = readTexture("122778280-white-gold-marble-texture-pattern-background-with-high-resolution-design-for-cover-book-or-brochure.png");
    metal = readTexture("gray-background-7131-96d780fd18d4eaf58a7331d45573204e@1x.png");
    color_for_enemy = readTexture("army-green-color-solid-background-1920x1080.png");
    color_for_flyenemy = readTexture("cbcf36e2111726b97b3ba02b4c176bdd.png");    
    color_cursor = readTexture("index.png");
    color_of_explore = readTexture("images.png");

    terrain.setTexture(stones);
    cursorMesh.setTexture(color_cursor);
    baseMesh.setTexture(bricks);
   explores.setTexture(color_of_explore);
}



void freeOpenGLProgram(GLFWwindow* window) {
    freeShaders();
    glDeleteTextures(1, &stones);
    glDeleteTextures(1, &bricks);
    glDeleteTextures(1, &color_for_enemy);
    glDeleteTextures(1, &color_for_flyenemy);
    glDeleteTextures(1, &metal);
    glDeleteTextures(1, &color_cursor);
    glDeleteTextures(1, &color_of_explore);
}

void drawScene(GLFWwindow* window) {
    GLfloat light3_diffuse[] = {1.0f,1.0f,1.0f};
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    M = glm::mat4(1.0f);
    V = glm::lookAt(glm::vec3(player.pos.x, 5.0f, player.pos.z), glm::vec3(player.pos.x, 1.0f, player.pos.z + 3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    P = glm::perspective(glm::radians(50.0f), 1.0f, 0.01f, 50.0f);

glMatrixMode(GL_PROJECTION);
glLoadMatrixf(value_ptr(P));
GLfloat light3_position[] = {5.0f,10.0f,20.0f};
GLfloat light3_spot_direction[] = {5.0f,Functions::getHeight(5.0f,14.0f,0.2f),14.0f};
glEnable(GL_LIGHT3);
glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 180);
glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3_spot_direction);
glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 25.0);

general_light->Enable();

    displayCursor();
    displayEnemies();
    displayTowers();
    displayBase();
    //displayBoom(basePosition);
    terrain.draw(P, V, M);
    
general_light->Disable();
    glfwSwapBuffers(window);
}

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        fprintf(stderr, "Nie można zainicjować GLFW.\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(1200, 800, "OpenGL", NULL, NULL);

    if (!window) {
        fprintf(stderr, "Nie można utworzyć okna.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Nie można zainicjować GLEW.\n");
        exit(EXIT_FAILURE);
    }

    initOpenGLProgram(window);

general_light = new light();


    restartGame();
    glfwSetTime(0);
    while (!glfwWindowShouldClose(window)) {
        
        printf("cash: %d, hp: %d, enemies: %d\n", player.cash, player.hp, (int)enemies.size() + (int)flying_enemies.size());

          if(player.hp<=0)
              lose(window);

        double interval = glfwGetTime();
        player.update_position(interval, basePosition);
        enemiesMove(interval);
        towersShoot();
        glfwSetTime(0);
        drawScene(window);

        glfwPollEvents();
        
        glDisable(GL_LIGHT3);
    }

    freeOpenGLProgram(window);
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
