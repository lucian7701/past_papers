#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

void movement(int& row, int& column, const char compass_char);
bool correct_destination(const char* path, char** m, int entrance_row, int entrance_column, int exit_row, int exit_column);
bool findPathRecursive(char** m, char start, char end, int height, int width, int current_row, int current_column, char* found_path, int path_index);

/* helper function which allocates a dynamic 2D array */
//returns a char **
char **allocate_2D_array(int rows, int columns) {
  //set char** to a new array of char*'s 
  char **m = new char *[rows];
  //if m =0/false then abort.
  assert(m);
  for (int r=0; r<rows; r++) {
    //set each char* in m to be a new column. 
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* helper function for internal use only which gets the dimensions of a maze */
bool get_maze_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  //get a line from input of a string of up to 511 characters long. 
  input.getline(line,512);  

  while (input) {
    //if the string length of the input line is greater than the width
    if ( (int) strlen(line) > width)
      //set the width to be that. 
      width = strlen(line);
    //increment the height and get the next line. 
    height++;
    input.getline(line,512);  
  }
  //This will eventually set the width to be the greatest width in the file. 

  //height will be set after it has gone through all lines.
  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

  //get the dimensions of the input file.
  bool success = get_maze_dimensions(filename, height, width);
  
  //error handling if dimensions not recieved 
  if (!success)
    return NULL;

  //create a pointer to a char pointer to allocate the 2D array. using the height and width. 
  char **m = allocate_2D_array(height, width);
  
  //load the input file
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    //set each line to the line char array
    input.getline(line, 512);
    //copy the char array to m[r]. each row of m.
    strcpy(m[r], line);
  }
  //m is now the maze. 
  return m;
}

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width) {
  //no relevant to fully understand. move on.
  //set width for before the grid. 
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
      cout << m[r][c];
    cout << endl;
  }
}

//question 1
bool find_marker(const char marker, char** m, int height, int width, int& row, int& column) {


  for (int r = 0; r<height; r++) {
    for (int c = 0; c<width; c++) {
      if (m[r][c] == marker) {
        row = r;
        column = c;
        return true;
      }
    }
  }
  
  row = -1;
  column = -1;
  return false;

}

//question 2

bool valid_solution(const char* path, char** m, int height, int width) {

  //does the given path go from entrance marker to exit marker, without going through a hedge. 

  //does it go from entrance to exit?
  //get entrance position
  int entrance_row, entrance_column;
  find_marker('>', m, height, width, entrance_row, entrance_column);

  int exit_row, exit_column;
  find_marker('X', m, height, width, exit_row, exit_column);

  return (correct_destination(path, m, entrance_row, entrance_column, exit_row, exit_column));

}

//translate character to change in row and column. 
void movement(int& row, int& column, const char compass_char) {
  switch (compass_char) { 
    case 'N':
      row--;
      break;
    case 'S':
      row++;
      break;
    case 'E':
      column++;
      break;
    case 'W':
      column--;
      break;
    default:
      cout << "Invlaid compass direction passed" << endl;
      break;
  }

}

bool correct_destination(const char* path, char** m, int entrance_row, int entrance_column, int exit_row, int exit_column) {

  int index = 0;
  while (path[index] != '\0') {
    movement(entrance_row, entrance_column, path[index]);
    if (m[entrance_row][entrance_column] != ' ' && m[entrance_row][entrance_column] != '>' && m[entrance_row][entrance_column] != 'X') {
      return false;
    }
    if (entrance_row == exit_row && entrance_column == exit_column) {
      return true;
    }
    index++;
  }

  return false;

}

//question 3

const char* find_path(char** m, int height, int width, char start, char end) {

  //find the position of the > and the X. Set the position of > to current row and current column.
  int current_row, current_column;
  find_marker('>', m, height, width, current_row, current_column);
  
  int path_index = 0;
  char* found_path = new char[height * width + 1];
  found_path[0] = '\0';

  if(!findPathRecursive(m, start, end, height, width, current_row, current_column, found_path, path_index)) {
    strcpy(found_path, "no solution");
  }

  return found_path;

}

const char compass_directions[4] = {'N', 'E', 'S', 'W'};

bool findPathRecursive(char** m, char start, char end, int height, int width, int current_row, int current_column, char* found_path, int path_index) {

  // cout << "recursion begins" << endl;
  //base case is if the solution is valid or if the current row and column are occupied. 
 
  if (m[current_row][current_column] != ' ' && m[current_row][current_column] != 'X' && m[current_row][current_column] != '>' || current_row < 0 || current_row >= height || current_column <0 || current_column >= width) {
    
    // cout << "hits a blocker" << endl;
    return false;

  }

  

  if (m[current_row][current_column] == end) {
    // cout << "end is true" << endl;
    m[current_row][current_column] = '#';
    found_path[path_index] = '\0';
    return true;
  }

  
  m[current_row][current_column] = '#';

  for (int i=0; i<4; i++) {
    // cout << compass_directions[i] << endl;
    int dummy_current_row = current_row;
    // cout << "dummy current row " << dummy_current_row << endl;
    int dummy_current_column = current_column;
    // cout << "dummy current column " << dummy_current_row << endl;
    movement(dummy_current_row, dummy_current_column, compass_directions[i]);
    // cout << "after " << dummy_current_row << endl;
    // cout << "after " << dummy_current_column << endl;

    // cout << "another recursion" << endl;
    if (findPathRecursive(m, start, end, height, width, dummy_current_row, dummy_current_column, found_path, path_index + 1)) {
      // cout << "does it get here" << endl;
      found_path[path_index] = compass_directions[i];
      
      return true;
      // m[current_row][current_column] = '#';
    }
   
  }

  m[current_row][current_column] = ' ';

  return false;

}




