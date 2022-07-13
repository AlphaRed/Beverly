#ifndef MAP_H
#define MAP_H

int loadMap(char *filename);
void setupMapTiles(SDL_Rect t[], int num);
int loadHeightMap(char *filename);

#endif