#include "Enemy.h"
class FlyingEnemy : public Enemy{
  public:
    FlyingEnemy();
    void move(double interval);
};