#ifndef MAP_H
#define MAP_H

extern int levelMap[MAX_MAP_SIZE][MAX_MAP_SIZE];
extern int heightMap[MAX_MAP_SIZE][MAX_MAP_SIZE];

int loadMap(char *filename);
void setupMapTiles(SDL_Rect t[], int num);
int loadHeightMap(char *filename);

#endif