#include"common.h"

// load from file function
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

// tile loading?