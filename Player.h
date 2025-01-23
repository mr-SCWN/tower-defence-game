#include <glm/ext/vector_float3.hpp>
class Player{
  public:
    glm::vec3 pos;
    glm::vec3 speed;
    glm::vec3 cursor;
    int cash;
    int hp;
  
    Player();
    void update_position(double interval, glm::vec3 basePosition);
};