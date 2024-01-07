#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include "laser.h"

using namespace std;


void move_laser(Direction& direction, char** board, int& last_row, int& last_col);
Direction direction_helper(char ch, Direction direction);

/* pre-supplied helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **array = new char *[rows];
  assert(array);
  for (int r=0; r<rows; r++) {
    array[r] = new char[columns];
    assert(array[r]);
  }
  return array;
}

/* pre-supplied helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **array, int rows) {
  for (int r=0; r<rows; r++)
    delete [] array[r];
  delete [] array;
}

/* internal helper function which gets the dimensions of a board */
bool get_board_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* internal helper function which removes carriage returns and newlines from end of strings */
void filter (char *line) {
  while (*line) {
    if (!isprint(*line))
     *line = '\0';
    line++;
  }
}

/* pre-supplied function to load a board from a file*/
char **load_board(const char *filename, int &height, int &width) {

  bool success = get_board_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **board = allocate_2D_array(height, width + 1);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    filter(line);
    strcpy(board[r], line);
  }
  
  return board;
}

/* pre-supplied function to print a board */
void print_board(char **board, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << board[r][c];
    cout << endl;
  }
}

/* add your own function definitions here */

// Question 1
bool find_laser(char** board, int height, int width, int& row) {

  for (int i=0; i<height-2; i++) {
    if (board[i][0] == '>') {
      row = i;
      return true;
    }

  }

  row = -1;
  return false;
}

// Question 2
char mirror_label(char** board, int height, int width, int row, int column) {


  //mirror is at row, col
  //look through all surrounding squares.

  char mirror = board[row][column];

  if (mirror != '/' && mirror != '\\') {
    return '\0';
  } 

  //find a possible attached character. 
  for (int r=-1; r<=1; r++) {
    for (int c=-1; c<=1; c++) {

      if (r == 0 || c == 0) {
        continue;
      }

      if (mirror == '/') {
        if (r == c) {
          continue;
        }
      }

      if (mirror == '\\') {
        if (r != c) {
          continue;
        }

      }


      char ch = board[row+r][column+c];
      // cout << ch << endl;
      if (isalpha(ch)) {
        return ch;
      }

    }
  }

  return '\0';

}


// Question 3
bool shoot(char** board, int height, int width, char message[], int& last_row, int& last_col) {

  //clear board before shoot
  for (int r=1; r<height; r++) {
    for (int c=1; c<width; c++) {
      
      if (board[r][c] == '-' || board[r][c] == '|' || board[r][c] == '+') {
        board[r][c] = ' ';
      }

    }
  }
  
  last_row = 0;
  last_col = 0;
  //a function which moves the laser beam forward one step is extremely useful
  Direction direction = EAST;
  if (last_col == 0) {
    find_laser(board, height, width, last_row);
  }
  
  message[0] = '\0';
  int message_index = 0;

  while (board[last_row][last_col] != '?' && board[last_row][last_col] != '#') {

    // cout << "moving laser" << endl;
    move_laser(direction, board, last_row, last_col);

    if ((board[last_row][last_col] == '\\' || board[last_row][last_col] == '/') && mirror_label(board, height, width, last_row, last_col) != '\0') {
      //add the character to message
      message[message_index] = mirror_label(board, height, width, last_row, last_col);
      message_index++;
      message[message_index] = '\0';

    } 

    if (board[last_row][last_col] == '@') {
      return true;
    }

  }


  return false;
}


//function which moves laser forward one step. 
void move_laser(Direction& direction, char** board, int& last_row, int& last_col) {

  char character_to_place;
  //switch statement for direction
  switch (direction) {

    case NORTH:
      last_row--;
      character_to_place = '|';
      break;
    case EAST:
      last_col++;
      character_to_place = '-';
      break;
    case SOUTH:
      last_row++;
      character_to_place = '|';
      break;
    default:
      last_col--;
      character_to_place = '-';
      break;
  }

  if (board[last_row][last_col] == ' ') {
    
    board[last_row][last_col] = character_to_place;

  } else if (board[last_row][last_col] == '-' || board[last_row][last_col] == '|') {
    
    board[last_row][last_col] = '+';
   
  } 
  

  if (board[last_row][last_col] == '/' || board[last_row][last_col] == '\\') {
    direction = direction_helper(board[last_row][last_col], direction);
  } 

}

Direction direction_helper(char ch, Direction direction) {

  if ((ch == '/' && direction == EAST) || (ch == '\\' && direction == WEST)) {
    return NORTH;
  } else if ((ch == '/' && direction == SOUTH) || (ch == '\\' && direction == NORTH)) {
    return WEST;
  } else if ((ch == '/' && direction == NORTH) || (ch == '\\' && direction == SOUTH)) {
    return EAST;
  } else if ((ch == '/' && direction == WEST) || (ch == '\\' && direction == EAST)) {
    return SOUTH;
  }

  else {
    return direction;
  }

}


// Question 4
char replacements[3] = {'/', '\\', ' '};


bool solve(char** board, int height, int width, const char* target, int row, int col) {

  char message[512];
  col = 0;
  //base case
  if (shoot(board, height, width, message, row, col)) {

    if (!strcmp(message, target)) {
      return true;
    }
    return false;
  }

  for (int r=1; r<height; r++) {
    for (int c=1; c<width; c++) {
      
      if (board[r][c] == '-' || board[r][c] == '|' || board[r][c] == '+') {
        board[r][c] = ' ';
      }

    }
  }

  if (board[row][col] == '?') {

    for (int i=0; i<3; i++) {
      
      board[row][col] = replacements[i];

      // cout << board[row][col] << endl;
      //refresh the board
      
      


      // cout << row << col << "here" << endl;
      if (solve(board, height, width, target, row, col)) {

        return true;

      }

      board[row][col] = '?';

    }


  }

  return false;

}