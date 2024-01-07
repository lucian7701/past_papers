/* pre-supplied function and type declarations */

char **allocate_2D_array(int rows, int columns);
void deallocate_2D_array(char **array, int rows);
char **load_board(const char *filename, int &height, int &width);
void print_board(char **board, int height, int width);

enum Direction {NORTH, EAST, SOUTH, WEST};

/* add your own function and type declarations here */

// Question 1
/* scans the
leftmost column of the height × width 2D array of characters board for the
character ’>’ (representing the laser). Where the leftmost column of board
contains the character, output parameter row should contain the correspond-
ing row index, and the function should return true; otherwise row should be
set to -1 and the function should return false. */
bool find_laser(char** board, int height, int width, int& row);

// Question 2
/* returns the alphabetical character label (if any) attached to the mirror found at
coordinates (row, column) within the height × width 2D array of characters
board. If there is no mirror at the coordinates, or if there is no alphabetical
character attached then the function should return the character ’\0’. */
char mirror_label(char** board, int height, int width, int row, int column);


// Question 3
/* plots the path of the laser beam across the given board,
updating board and output string message appropriately. The output pa-
rameters last row and last col should be set to the final coordinates of the
laser beam, which should terminate at an edge, the laser light absorber or a
’?’. The function should return true if and only if the final coordinates of
the laser beam correspond to the laser light absorber.
If the laser beam encounters a ’?’ or a ’#’ (edge) then the function should
terminate with a return value of false, message should reflect the letters
accumulated by the laser beam so far, and last row and last col should be
set to the coordinates of the encountered ’?’ or ’#’. */
bool shoot(char** board, int height, int width, char message[], int& last_row, int& last_col);

// Question 4
/* takes in a board containing ’?’ characters and replaces each of these by
a ’/’, a ’\’ or a ’ ’ (space) in such a way that the laser beam (a) accumulates
the message given by input string target and (b) terminates at the laser light
absorber. If these objectives can be met, the function should return true;
otherwise the function should return false. */
bool solve(char** board, int height, int width, const char* target, int row=0, int col=0);