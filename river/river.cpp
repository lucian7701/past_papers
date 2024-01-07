#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>

using namespace std;

#include "river.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

void removeFirstOccurrance(char* str, char charToRemove);

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new (nothrow) char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new (nothrow) char[columns];
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

/* pre-supplied function which creates an empty ASCII-art scene */
char **create_scene() {
  char **scene = allocate_2D_array(SCENE_HEIGHT, SCENE_WIDTH);

  for (int i=0; i<SCENE_HEIGHT; i++) 
    for (int j=0; j<SCENE_WIDTH; j++)
      scene[i][j] = ' ';

  return scene;
}

/* pre-supplied function which frees up memory allocated for an ASCII-art scene */
void destroy_scene(char **scene) {
  deallocate_2D_array(scene, SCENE_HEIGHT);
}

/* pre-supplied function which displays an ASCII-art scene */
void print_scene(char **scene) {
  for (int i=0; i<SCENE_HEIGHT; i++) {
    for (int j=0; j<SCENE_WIDTH; j++)
      cout << scene[i][j];
    cout << endl;
  }
}

/* helper function which removes carriage returns and newlines from strings */
void filter(char *line) {
  while (*line) {
    if (*line >= ' ')
      line++;
    else 
      *line = '\0';
  }
}

/* pre-supplied function which inserts an ASCII-art drawing stored in a file
   into a given ASCII-art scene starting at coordinates (row,col)  */
bool add_to_scene(char **scene, int row, int col, const char *filename) {

  ifstream in(filename);
  if (!in)
    return false;

  int start_col = col;
  char line[512];
  in.getline(line,512);
  filter(line);
  while (!in.fail()) {
    for (int n=0; n<strlen(line); n++) {
      if (row >= SCENE_HEIGHT)
	return false;
      if (col >= SCENE_WIDTH)
	break;
      scene[row][col++] = line[n];
    }
    row++;
    col = start_col;
    in.getline(line,512);
    filter(line);
  }
  return true;
}

/* pre-supplied helper function to report the status codes encountered in Question 3 */
const char *status_description(int code) {
  switch(code) {
  case ERROR_INVALID_CANNIBAL_COUNT:
    return "Invalid cannibal count";
  case ERROR_INVALID_MISSIONARY_COUNT:
    return "Invalid missionary count";
  case ERROR_INVALID_MOVE:
    return "Invalid move";
  case ERROR_MISSIONARIES_EATEN:
    return "The missionaries have been eaten! Oh dear!";
  case ERROR_INPUT_STREAM_ERROR:
    return "Unexpected input stream error";
  case ERROR_BONUS_NO_SOLUTION:
    return "No solution";
  case VALID_GOAL_STATE:
    return "Problem solved!";
  case VALID_NONGOAL_STATE:
    return "Valid state, everything is OK!";
  }
  return "Unknown error";
}


/* insert your functions here */
char** make_river_scene(const char* left, const char* boat) {

  // if (strlen(left) > 7) {
  // perform string invalid input handing. 
  // }

  char ** scene = create_scene();

  //fixed features
  add_to_scene(scene, 0, 0, "bank.txt");
  add_to_scene(scene, 0, 53, "bank.txt");
  add_to_scene(scene, 3, 30, "sun.txt");
  add_to_scene(scene, 19, 19, "river.txt");

  //character on the boat
  //use these for correlation between boat and passenger.
  // add_to_scene(scene, 11, 39, "missionary.txt");
  // add_to_scene(scene, 11, 45, "missionary.txt");

  //variable characters based upon inputs
  //positions of characters and boat:

  int boat_column = 36;
  
  int missionary_bank_row = 2;
  int cannibals_bank_row = 11;
  int left_bank_column[3] = {1, 7, 13};
  int right_bank_column[3] = {54, 60, 66};
  
  int missionaries_left_count = 0;
  int cannibals_left_count = 0;

  int missionaries_boat_count = 0;
  int cannibals_boat_count = 0;

  //contents of left bank 
  for (int i=0; i<strlen(left); i++) {
    
    if (left[i] == 'B') {
      boat_column = 19;
    }
    if (left[i] == 'M') {
      missionaries_left_count++;
    }
    if (left[i] == 'C') {
      cannibals_left_count++;
    }

  }

  for (int i=0; i<strlen(boat); i++) {
    if (boat[i] == 'M') {
      missionaries_boat_count++;
    }
    if (boat[i] == 'C') {
      cannibals_boat_count++;
    }

  }

  int missionaries_right_count = 3-missionaries_left_count-missionaries_boat_count;
  int cannibals_right_count = 3-cannibals_left_count-cannibals_boat_count;
  int boat_count = 0;

  //add boat to the scene
  add_to_scene(scene, 17, boat_column, "boat.txt");

  //add missionaries
  //add missionaries to the left bank;
  for (int i=0; i<missionaries_left_count; i++) {
    add_to_scene(scene, missionary_bank_row, left_bank_column[i], "missionary.txt");
  }

  //add missionaries to right bank;
  for (int i=0; i<missionaries_right_count; i++) {
    add_to_scene(scene, missionary_bank_row, right_bank_column[i], "missionary.txt");
  }

  //add missionaries to boat;
  for (int i=0; i<missionaries_boat_count; i++) {
    int passenger_position = boat_column + 3 + (6* boat_count);
    add_to_scene(scene, 11, passenger_position, "missionary.txt");
    boat_count++;
  }

  //add cannibals
  //add cannibals to left bank;
  for (int i=0; i<cannibals_left_count; i++) {
    add_to_scene(scene, cannibals_bank_row, left_bank_column[i], "cannibal.txt");
  }

  //add cannibals to right bank;
  for (int i=0; i<cannibals_right_count; i++) {
    add_to_scene(scene, cannibals_bank_row, right_bank_column[i], "cannibal.txt");
  }

  //add cannibals to boat;
  for (int i=0; i<cannibals_boat_count; i++) {
    int passenger_position = boat_column + 3 + (6* boat_count);
    add_to_scene(scene, 11, passenger_position, "cannibal.txt");
    boat_count++;
  }

  if (missionaries_boat_count+missionaries_left_count+missionaries_right_count !=3) {
    cout << status_description(-2) <<endl;
  }
  if (cannibals_boat_count+cannibals_left_count+cannibals_right_count!=3) {
    cout << status_description(-1) <<endl;
  }
  
  return scene;

}

int perform_crossing(char* left, const char* targets) {

  
  //part 1 loading the boat
  cout << "Loading the boat..." << endl;

  
  
  //targets are transfered from the bank where the boat is, onto the boat.
  //create a new scene where the targets are moved onto the boat. 
  //if target is M and the boat is on the right, it should stay as left, target. 
  //but if the boat is on the left, it should remove the appropriate letters
  //from left string. 
  bool is_boat_left = false;
  for (int i=0; i<strlen(left); i++) {
    if (left[i] == 'B') {
      is_boat_left = true;
    }
  }

  if (is_boat_left) {
    for (int j=0; j<strlen(targets); j++) {
      removeFirstOccurrance(left, targets[j]);
    }
  }

  char** scene = make_river_scene(left,targets);

  print_scene(scene);
  cout<<endl;
  destroy_scene(scene);

  //cross the river.
  if (is_boat_left) {
    removeFirstOccurrance(left, 'B');
    is_boat_left = false;
  } else {
    left[strlen(left)] = 'B';
    left[strlen(left)] = '\0';
    is_boat_left = true;
  }

  cout<< "Crossing the river..." << endl;
  char** scene1 = make_river_scene(left,targets);
  print_scene(scene1);
  cout<<endl;
  destroy_scene(scene1);

  //unloading the boat.
  if (is_boat_left) {
    strcat(left, targets);
  } 
  targets = "";

  char** scene_unload = make_river_scene(left,targets);
  print_scene(scene_unload);
  destroy_scene(scene_unload);

  cout << "Unloading the boat" << endl;

  //tally people no one in the boat at this point.
  int missionaries_left_count = 0;
  int missionaries_right_count = 0;
  int cannibals_left_count = 0;
  int cannibals_right_count = 0;

  //left bank
  for (int i=0; i<strlen(left); i++) {
    if (left[i] == 'M') {
      missionaries_left_count++;
    }
    if (left[i] == 'C') {
      cannibals_left_count++;
    }
  }
  missionaries_right_count = 3-missionaries_left_count;
  cannibals_right_count = 3-cannibals_left_count;

  if (((missionaries_right_count < cannibals_right_count) && missionaries_right_count > 0) || ((missionaries_left_count < cannibals_left_count) && missionaries_left_count > 0)) {
    return -4;
  } 
  if (missionaries_right_count ==3 && cannibals_right_count == 3) {
    return 2;
  }

  return 1;

}

void removeFirstOccurrance(char* str, char charToRemove) {

  int i=0, j=0;
  bool found = false;

  while (str[i] != '\0') {
    if (str[i] == charToRemove && !found) {
      found = true;
      i++;
    }
    str[j++] = str[i++];
  }
  str[j] = '\0';
}

//question 3

int play_game() {

  cout << "This is the starting board." << endl;

  char left[10] = "BCCCMMM";
  char** scene;
  scene = make_river_scene(left,"");
  print_scene(scene);
  destroy_scene;

  char* targets;

  int status = 1;

  while (status == 1) {
    cout << "Please enter which characters you would like to load onto the boat (up to 2 characters M or C)" << endl;
    cin >> targets;

    status = perform_crossing(left, targets);
  }

  return status;
  

  
}