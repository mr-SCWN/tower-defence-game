LIBS=-lGL -lglfw -lGLEW
HEADERS=Cursor.h default_tower.h Enemy.h Player.h shaderprogram.h Terrain.h Drawable.h default_tower_DATA.h enemy_DATA.h Functions.h lodepng.h Tower.h FlyingEnemy.h Base.h Base_DATA.h Boom.h Boom_DATA.h light.h
FILES=Cursor.cpp default_tower.cpp Enemy.cpp main_file.cpp Player.cpp shaderprogram.cpp Drawable.cpp Terrain.cpp Functions.cpp lodepng.cpp Tower.cpp FlyingEnemy.cpp Base.cpp Boom.cpp light.cpp
main: $(FILES) $(HEADERS) $(LIBS)
	g++ -o main $(FILES) $(HEADERS) $(LIBS) -I.


# LIBS=-lGL -lglfw -lGLEW
# HEADERS=cursor.h default_tower.h enemy.h hand_tower.h magic_tower.h Player.h shaderprogram.h
# FILES=cursor.cpp default_tower.cpp enemy.cpp hand_tower.cpp magic_tower.cpp main_file.cpp Player.cpp shaderprogram.cpp
# main: $(FILES) $(HEADERS) $(LIBS)
# 	g++ -o main $(FILES) $(HEADERS) $(LIBS) -I.
