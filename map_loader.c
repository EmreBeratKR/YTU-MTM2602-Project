#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include "map_loader.h"


#define MAP_FILE_PATH "map_builder/map.txt"
#define INF 999999

#define TILE_PLAIN 0
#define TILE_HILL 1
#define TILE_WALL 2

#define TILE_COST_PLAIN 1
#define TILE_COST_HILL 5
#define TILE_COST_WALL INF
#define TILE_COST_INVALID -1


int MAP_WIDTH;
int MAP_HEIGHT;
int TILE_NUMBER;
int ACTIONS_NUMBER;
float PATH_COSTS[MAX_ROWS * MAX_COLS][MAX_ROWS * MAX_COLS];
float SLD[MAX_ROWS * MAX_COLS][MAX_ROWS * MAX_COLS];

char CHAR_BUFFER[50];


void tile_to_xy(Tile tile, int* x, int* y)
{
    *x = tile % MAP_WIDTH;
    *y = (tile - *x) / MAP_WIDTH;
}

const char* tile_to_string(Tile tile)
{
    int x, y;
    tile_to_xy(tile, &x, &y);

    char letter = 'A' + y;

    sprintf(CHAR_BUFFER, "%c%d", letter, x + 1);

    return CHAR_BUFFER;
}

void print_tile(Tile tile)
{
    printf("%s", tile_to_string(tile));
}

void print_action(ACTIONS action)
{
    printf("Go_%s", tile_to_string((Tile) action));
}

void load_map() 
{
    int matrix[MAX_ROWS][MAX_COLS];
    FILE *file;
    int rows = 0, cols = 0;

    // Open the file for reading
    file = fopen(MAP_FILE_PATH, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", MAP_FILE_PATH);
        return;
    }

    // Read data from the file
    char line[100]; // Assuming maximum line length is 100 characters
    while (fgets(line, sizeof(line), file) != NULL && rows < MAX_ROWS) 
    {
        char* token = strtok(line, ",");
        cols = 0;

        while (token != NULL) 
        {
            matrix[rows][cols++] = atoi(token);
            token = strtok(NULL, ",");
        }

        rows++;
    }

    // Close the file
    fclose(file);

    MAP_WIDTH = cols;
    MAP_HEIGHT = rows;
    TILE_NUMBER = rows * cols;
    ACTIONS_NUMBER = TILE_NUMBER;

    int xA, yA, xB, yB;
    for (int tileA = 0; tileA < TILE_NUMBER; tileA++)
    {
        tile_to_xy(tileA, &xA, &yA);

        for (int tileB = 0; tileB < TILE_NUMBER; tileB++)
        {
            tile_to_xy(tileB, &xB, &yB);
            
            float pathCost;
            int deltaX = abs(xA - xB);
            int deltaY = abs(yA - yB);
            int deltaTotal = deltaX + deltaY;

            if (tileA == tileB)
            {
                pathCost = 0;
            }

            else if (deltaTotal > 1)
            {
                pathCost = TILE_COST_INVALID;
            }

            else
            {
                switch (matrix[yB][xB])
                {
                case TILE_PLAIN:
                    pathCost = TILE_COST_PLAIN;
                    break;
                case TILE_HILL:
                    pathCost = TILE_COST_HILL;
                    break;
                case TILE_WALL:
                    pathCost = TILE_COST_WALL;
                    break;
                default:
                    pathCost = TILE_COST_INVALID;
                    break;
                }   
            }

            PATH_COSTS[tileA][tileB] = pathCost;
            SLD[tileA][tileB] = sqrtf(deltaX * deltaX + deltaY * deltaY);
        }
    }
    
    printf("======================== MAP ========================\n");
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("=====================================================\n");

    printf("MAP_WIDTH: %d\n", MAP_WIDTH);
    printf("MAP_HEIGHT: %d\n", MAP_HEIGHT);
    printf("TILE_NUMBER: %d\n", TILE_NUMBER);
    printf("ACTIONS_NUMBER: %d\n", ACTIONS_NUMBER);
    printf("===================== PATH COSTS =====================\n");
    for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++) 
    {
        for (int j = 0; j < MAP_WIDTH * MAP_HEIGHT; j++) 
        {
            if (PATH_COSTS[i][j] == INF)
            {
                printf(" INF,");
                continue;
            }

            else if (PATH_COSTS[i][j] < 0)
            {
                printf("  -1,");
                continue;
            }

            printf("   %d,", (int) PATH_COSTS[i][j]);
        }
        printf("\n");
    }

    printf("======================== SLD ========================\n");
    for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++) 
    {
        for (int j = 0; j < MAP_WIDTH * MAP_HEIGHT; j++) 
        {
            printf("%.2f ", SLD[i][j]);
        }
        printf("\n");
    }
    printf("=====================================================\n");
}
