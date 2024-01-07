#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

#include "tube.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

void move_position(int& current_row, int& current_col, Direction direction);
void get_station_from_symbol(char destination[512], char ch);

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* internal helper function which gets the dimensions of a map */
bool get_map_dimensions(const char *filename, int &height, int &width) {
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

/* pre-supplied function to load a tube map from a file*/
char **load_map(const char *filename, int &height, int &width) {

  bool success = get_map_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];
  char space[] = " ";

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
    while ( (int) strlen(m[r]) < width )
      strcat(m[r], space);
  }
  
  return m;
}

/* pre-supplied function to print the tube map */
void print_map(char **m, int height, int width) {
  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(2) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

/* pre-supplied helper function to report the errors encountered in Question 3 */
const char *error_description(int code) {
  switch(code) {
  case ERROR_START_STATION_INVALID: 
    return "Start station invalid";
  case ERROR_ROUTE_ENDPOINT_IS_NOT_STATION:
    return "Route endpoint is not a station";
  case ERROR_LINE_HOPPING_BETWEEN_STATIONS:
    return "Line hopping between stations not possible";
  case ERROR_BACKTRACKING_BETWEEN_STATIONS:
    return "Backtracking along line between stations not possible";
  case ERROR_INVALID_DIRECTION:
    return "Invalid direction";
  case ERROR_OFF_TRACK:
    return "Route goes off track";
  case ERROR_OUT_OF_BOUNDS:
    return "Route goes off map";
  }
  return "Unknown error";
}

/* presupplied helper function for converting string to direction enum */
Direction string_to_direction(const char *token) {
  const char *strings[] = {"N", "S", "W", "E", "NE", "NW", "SE", "SW"};
  for (int n=0; n<8; n++) {
    if (!strcmp(token, strings[n])) 
      return (Direction) n;
  }
  return INVALID_DIRECTION;
}

//question 1
bool get_symbol_position(char** map, int height, int width, char target, int& r, int& c) {

  for (int row=0; row<height; row++) {
    for (int col=0; col< width; col++) {

      if (map[row][col] == target) {
        r = row;
        c = col;
        return true;
      }

    }
  }

  r = -1;
  c = -1;

  return false;
}

//question 2
char get_symbol_for_station_or_line(const char* name) {

  char buffer[512];
  char character = ' ';
  char station_or_line[512];
  // char reference_letter = '_';
  //this will require an input stream from stations.txt
  ifstream in;
  in.open("stations.txt");

  bool found = false;
  while (!in.eof() && !found) {
    
    in.getline(buffer, 512);
    int index = 0;
    character = buffer[0];
    while (buffer[index+2] != '\0') {
      station_or_line[index] = buffer[index+2];
      index++;
    }
    station_or_line[index] = '\0';

    if (!strcmp(station_or_line, name)) {
      found = true;
    }
    
  }
  
  in.close();

  in.open("lines.txt");

  while (!in.eof() && !found) {
    
    in.getline(buffer, 512);
    int index = 0;
    character = buffer[0];
    while (buffer[index+2] != '\0') {
      station_or_line[index] = buffer[index+2];
      index++;
    }
    station_or_line[index] = '\0';

    if (!strcmp(station_or_line, name)) {
      found = true;
    }
    
  }
  
  in.close();

  if (found) {
    return character;
  } else {
    return ' ';
  }
  
}

int validate_route(char** map, int height, int width, const char* start_station, const char* route, char destination[512]) {

  //handle invalid start station
  char station = get_symbol_for_station_or_line(start_station);
  // cout << "station is" << station << endl;
  if (isalnum(station) == 0) {
    return ERROR_START_STATION_INVALID;
  }

  //handle invalid direction

  //put the letters between commas into an array of strings.
  //some way to put the route string into an array of Direction enum. 
  //route is a string
  int route_string_length = strlen(route);
  int route_length = 1;

  for (int i=0; i<route_string_length; i++) {
    if (route[i] == ',') {
      route_length++;
    }
  }
  // cout << "route length is" << route_length <<  endl;

  Direction enum_route[route_length];
  char compass[3];
  int compass_index = 0;
  int enum_route_index = 0;

  for (int i=0; i<=route_string_length; i++) {
    
    if (route[i] == ',' || route[i] == '\0') {
      Direction compass_direction = string_to_direction(compass);
      if (compass_direction == 8) {
        return ERROR_INVALID_DIRECTION;
      }
      enum_route[enum_route_index] = compass_direction;
      enum_route_index++;
      compass_index = 0;
      continue;
    }

    compass[compass_index] = route[i];
    compass_index++;
    compass[compass_index] = '\0';

  }

  int current_row;
  int current_col;
  
  get_symbol_position(map, height, width, station, current_row, current_col);

  int row_backtrack[route_length];
  int col_backtrack[route_length];

  int line_changes = 0;

  for (int i=0; i<route_length; i++) {

    
    char current_character = map[current_row][current_col];
    row_backtrack[i] = current_row;
    col_backtrack[i] = current_col;
    
    move_position(current_row, current_col, enum_route[i]);
    
    //if route strays out of bounds of the map return error
    if (current_row < 0 || current_row >= height || current_col < 0 || current_col >= width) {
      return ERROR_OUT_OF_BOUNDS;
    }
    //if route strays off track return error
    if (map[current_row][current_col] == ' ') {
      return ERROR_OFF_TRACK;
    }
    //if line hopping return error
    if (map[current_row][current_col] != current_character) {
        if (!isalnum(current_character) && !isalnum(map[current_row][current_col])) {
          return ERROR_LINE_HOPPING_BETWEEN_STATIONS;
        }
        if (i>1 && map[row_backtrack[i-1]][col_backtrack[i-1]] != map[current_row][current_col] && isalnum(current_character)) {
          line_changes++;
        }
    } 
    //if backtracking between stations
    if (i > 1 && current_row == row_backtrack[i-1] && current_col == col_backtrack[i-1] && !isalnum(map[row_backtrack[i]][col_backtrack[i]])) {
      return ERROR_BACKTRACKING_BETWEEN_STATIONS;
    }

  }

  if (!isalnum(map[current_row][current_col])) {
    return ERROR_ROUTE_ENDPOINT_IS_NOT_STATION;
  }

  get_station_from_symbol(destination, map[current_row][current_col]);


  

  return line_changes;

}

void move_position(int& current_row, int& current_col, Direction direction) {
  switch (direction) {
    case N:
      current_row--;
      break;
    case E: 
      current_col++;
      break;
    case S:
      current_row++;
      break;
    case W:
      current_col--;
      break;
    case NW:
      current_row--;
      current_col--;
      break;
    case NE:
      current_row--;
      current_col++;
      break;
    case SW:
      current_row++;
      current_col--;
      break;
    case SE:
      current_row++;
      current_col++;
      break;
    default:
      break;
  }

}

void get_station_from_symbol(char destination[512], char ch) {

  char buffer[512];

  ifstream in;
  in.open("stations.txt");

  

  while (!in.eof()) {
    in.getline(buffer, 512);

    if (buffer[0] == ch) {
      int index=2;
      while (buffer[index] != '\0') {
        destination[index-2] = buffer[index];
        index++;
      }
      destination[index-2] = '\0';
    }

    // cout << buffer << endl;
  }
  


  in.close();


}
