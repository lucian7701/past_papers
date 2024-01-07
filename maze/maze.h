/* You are pre-supplied with the functions below. Add your own 
   function prototypes to the end of this file. */

#ifndef MAZE_H
#define MAZE_H


/* helper functions to allocate and deallocate dynamic 2D arrays */
char **allocate_2D_array(int rows, int columns);
void deallocate_2D_array(char **m, int rows);

/* pre-supplied function to load a maze from a file */
char **load_maze(const char *filename, int &height, int &width);

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width);

//function to find a given marker input
bool find_marker(const char marker, char** m, int height, int width, int& row, int& column);

//function to tell if a given path is a valid solution
bool valid_solution(const char* path, char** m, int height, int width);

const char* find_path(char** m, int height, int width, char start, char end);


#endif
