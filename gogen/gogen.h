
/*  Pre-supplied functions for loading and printing board and word list */

char **load_board(const char *filename);
bool save_board(char **board, const char *filename);
void print_board(char **board);

char **load_words(const char *filename);
void print_words(char **words);

void delete_board(char **board);
void delete_words(char **words);

/* -----------8<-------------8<------------8<--------------8<------------ */

/* add your function prototypes here */

//Question 1 
/* searches for the first occurrence of character ch in a given board when searched in a row-by-row fashion. If the character is found,
the function should return true and set the output parameters row and column to the row and column
number (indexed starting from 0). If the character cannot be found, the function should return false
and row and column should both be set to -1. */
bool get_position(char** board, char ch, int& row, int& column);

//Question 2
/* returns true if the given board represents a solution to the Gogen puzzle with the given list of words. */
bool valid_solution(char** board, char** words);

//Question 3a
/* mutually updates the board and a mask for letter ch according to rules 

If ch is found in the board at position (r, c), then set every entry in mask to be false with the
exception of element (r, c), which should be set to true, and return from the function.

For every cell in the board that is marked with a letter (that is not ch), set the corresponding
element in mask to false.

If there is one (and only one) cell with the value true in mask then set the corresponding cell
in the board to ch.*/
void update(char** board, char ch, Mask& mask);

//Question 3b
/* modifies masks one and one by intersecting each with the 1-neighbourhood of the other. */
void neighbourhood_intersect(Mask& one, Mask& two);


//Question 4
/*find a solution to a given Gogen puzzle. If a solution can be found, parameter board should contain
the completed board. Otherwise the function should return false.*/
bool solve_board(char** board, char** words);

