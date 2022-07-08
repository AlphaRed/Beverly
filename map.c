#include"common.h"

// Loads map from file
int loadMap(char *filename)
{
    FILE *file = fopen(filename, "r");
    if(file == NULL)
    {
        printf("Error opening map file!\n");
        return 1;
    }
    for(int i = 0; i < MAX_MAP_SIZE; i++)
    {
        for(int j = 0; j < MAX_MAP_SIZE; j++)
        {
            if(fscanf(file, "%d", &levelMap[i][j]) == EOF)
                return 1;
        }
    }
    fclose(file);
    return 0;
}

// Setup map tiles to tile array
void setupMapTiles(SDL_Rect t[], int num)
{
    for(int i = 0; i < num; i++)
    {
        t[i].x = (i % 8) * TILE_SIZE;
        t[i].y = (i / 8) * TILE_SIZE;
        t[i].w = TILE_SIZE;
        t[i].h = TILE_SIZE;
    }
}

// height map loading

// tile loading

// draw map function