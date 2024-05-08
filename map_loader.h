#ifndef MAP_LOADER_H
#define MAP_LOADER_H


typedef int Tile;
typedef int ACTIONS;


#define MAX_ROWS 30
#define MAX_COLS 30


extern int MAP_WIDTH;
extern int MAP_HEIGHT;
extern int TILE_NUMBER;
extern int ACTIONS_NUMBER;
extern float PATH_COSTS[MAX_ROWS * MAX_COLS][MAX_ROWS * MAX_COLS];
extern float SLD[MAX_ROWS * MAX_COLS][MAX_ROWS * MAX_COLS];


void tile_to_xy(Tile tile, int* x, int* y);
const char* tile_to_string(Tile tile);
void print_tile(Tile tile);
void print_action(ACTIONS action);
void load_map();


#endif