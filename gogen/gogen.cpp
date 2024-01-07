#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>

#include "common.h"
#include "mask.h"
#include "gogen.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

bool next_letter_surrounds(char** board, char next_letter, int &row, int& col);
int letters_on_board(char** board);
bool is_letter_on_board(char** board, char letter);
bool recursive_solve(char** board, char** words);

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

/* internal helper function which removes unprintable characters like carriage returns and newlines from strings */
void filter (char *line) {
  while (*line) {
    if (!isprint(*line))
     *line = '\0';
    line++;
  }
}

/* loads a Gogen board from a file */
char **load_board(const char *filename) {
  char **board = allocate_2D_array(5, 6);
  ifstream input(filename);
  assert(input);
  char buffer[512];
  int lines = 0;
  input.getline(buffer, 512);
  while (input && lines < HEIGHT) {
    filter(buffer);
    if (strlen(buffer) != WIDTH)
      cout << "WARNING bad input = [" << buffer << "]" << endl;
    assert(strlen(buffer) == WIDTH);
    strcpy(board[lines], buffer);
    input.getline(buffer, 512);
    lines++;
  }
  input.close();
  return board;
}

/* saves a Gogen board to a file */
bool save_board(char **board, const char *filename) {
  ofstream out(filename); 
  if (!out)
    return false;
  for (int r=0; r<HEIGHT; r++) {
    for (int c=0; c<WIDTH; c++) {
      out << board[r][c];
    }
    out << endl;
  }
  bool result = out.good();
  out.close();
  return result;
}

/* internal helper function for counting number of words in a file */
int count_words(const char *filename) {
  char word[512];
  int count = 0;
  ifstream in(filename);
  while (in >> word)
    count++;
  in.close();
  return count;
}

/* loads a word list from a file into a NULL-terminated array of char *'s */
char **load_words(const char *filename) {
  int count = count_words(filename);
  ifstream in(filename);
  assert(in);
  int n=0;
  char **buffer = new char *[count+1]; // +1 because we NULL terminate 
  char word[512];
  for (; (in >> word) && n<count; n++) {
    buffer[n] = new char[strlen(word) + 1];
    strcpy(buffer[n], word);
  }
  buffer[n] = NULL;
  in.close();
  return buffer;
}

/* prints a Gogen board in appropriate format */
void print_board(char **board) {
  for (int r=0; r<HEIGHT; r++) {
    for (int c=0; c<WIDTH; c++) {
      cout << "[" << board[r][c] << "]";
      if (c < WIDTH-1)
	cout << "--";
    }
    cout <<endl;
    if (r < HEIGHT-1) {
      cout << " | \\/ | \\/ | \\/ | \\/ |" << endl;
      cout << " | /\\ | /\\ | /\\ | /\\ |" << endl;
    }
  }
}

/* prints a NULL-terminated list of words */
void print_words(char **words) {
  for (int n=0; words[n]; n++) 
    cout << words[n] << endl;
}

/* frees up the memory allocated in load_board(...) */
void delete_board(char **board) {
  deallocate_2D_array(board, HEIGHT);
}

/* frees up the memory allocated in load_words(...) */
void delete_words(char **words) {
  int count = 0;
  for (; words[count]; count++);
  deallocate_2D_array(words, count);
}

/* add your own function definitions here */
// Question 1

bool get_position(char** board, char ch, int& row, int& column) {

  for (int r=0; r<5; r++) {
    for (int c=0; c<5; c++) {
      if (board[r][c] == ch) {
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

//Question 2
bool valid_solution(char** board, char** words) {

  //for a given board. 
  //by moving one step each time, can each word be made.

  
  // if the second letter can not be found within one, return false;
  // continue for each letter and each word.  

  // cout << words[0] << endl;

  //For each word
  for (int n=0; words[n]; n++) {

    //Find the first letter
    int row;
    int col;
  
    get_position(board, words[n][0], row, col);

    //Find next letters
    for (int i=1; i<strlen(words[n]); i++) {
      
      if (!next_letter_surrounds(board, words[n][i], row, col)) {
        return false;
      }
    }
  }

  return true;

}

//helper function to determine if next letter surrounds current letter
bool next_letter_surrounds(char** board, char next_letter, int &row, int& col) {

  //for each next letter, is the letter of the word surrounding the current letter.
  for (int r=-1; r<=1; r++) {
    for (int c=-1; c<=1; c++) {

      if (row+r<0 || row+r >4 || col+c <0 || col+c>4 || (r==0 && c==0)) {
        continue;
      }
      if (board[row+r][col+c] == next_letter) {
        row = row+r;
        col = col+c;
        return true;
      }
    }
  }

  return false;

}

//Question 3a
void update(char** board, char ch, Mask& mask) {
  // If ch is found in the board at position (r, c), then set every entry in mask to be false with the
  // exception of element (r, c), which should be set to true, and return from the function.

  int row;
  int col;

  if (get_position(board, ch, row, col)) {
    mask.set_all(false);
    mask.set_element(row,col,true);
    return;
  }

  // For every cell in the board that is marked with a letter (that is not ch), set the corresponding
  // element in mask to false.
  for (int r=0; r<5; r++) {
    for (int c=0; c<5; c++) {
      if (isalpha(board[r][c]) && board[r][c] != ch) {
        mask.set_element(r,c,false);
      }
    }
  }

  // If there is one (and only one) cell with the value true in mask then set the corresponding cell
  // in the board to ch.
  int true_count=0;
  for (int r=0; r<5; r++) {
    for (int c=0; c<5; c++) {

      if (mask[r][c]) {
        row = r;
        col = c;
        true_count++;
      }

    }
  }
  if (true_count == 1) {
    board[row][col] = ch;
  }
}

//Question 3b
void neighbourhood_intersect(Mask& one, Mask& two) {

  //modifies masks by indersecting each with the 1-neighbourhood of the other. 
  //change each masks to their one neighbourhood.
  // one.print();
  // cout << endl;
  // two.print();
  // cout << endl;

  Mask neighbourhood_one = one.neighbourhood();
  Mask neighbourhood_two = two.neighbourhood();

  // neighbourhood_one.print();
  // cout << endl;
  // neighbourhood_two.print();
  // cout << endl;

  //Find their intersections.
  two.intersect_with(neighbourhood_one);
  one.intersect_with(neighbourhood_two);
  

  // one.print();
  // cout << endl;
  // two.print();
  // cout << endl;
  // neighbourhood_two.intersect_with(neighbourhood_one);
  // neighbourhood_one.print();
  // cout << endl;
  // neighbourhood_two.print();

}

//Question 4
bool solve_board(char** board, char** words) {

  // Create an array of 25 masks (one for each letter ’A’ to ’Y’) and use the update(...) function to
  // initialise them.
  Mask mask_array[25];

  int mask_index = 0;
  for (char i='A'; i<='Y'; i++) {

    //initialise the mask for each letter.
    update(board, i, mask_array[mask_index]);
    mask_index++;

  }

  //go through adjacent letters for all words. 
  
  // for each word
  //keep doing this until the number of letters on the board stops changing. This will require helper 
  //function to count number of letters. 


  int letters_on_board_before;
  int letters_on_board_after;
  
  do {
  letters_on_board_before = letters_on_board(board);
  
  for (int n=0; words[n]; n++) {
    for (int i=0; i<strlen(words[n])-1; i++) {
      
      
      // cout << "first mask array" << endl;
      // cout << words[n][i] << endl;
      // mask_array[words[n][i]-'A'].print();
      // cout << "second mask array" << endl;
      // cout << words[n][i+1] << endl;
      // mask_array[words[n][i+1]-'A'].print();

      neighbourhood_intersect(mask_array[words[n][i]-'A'], mask_array[words[n][i+1]-'A']);

      // cout << "first mask array after" << endl;
      // cout << words[n][i] << endl;
      // mask_array[words[n][i]-'A'].print();
      // cout << "second mask array after" << endl;
      // cout << words[n][i+1] << endl;
      // mask_array[words[n][i+1]-'A'].print();
      

      update(board, words[n][i], mask_array[words[n][i]-'A']);
      update(board, words[n][i+1], mask_array[words[n][i+1]-'A']);




    }
  }

  letters_on_board_after= letters_on_board(board);

  }

  while (letters_on_board_before < letters_on_board_after);


  //if not solved
  if (!valid_solution(board, words)) {

    recursive_solve(board, words);

  }
  //make recursive solve function.
  if (valid_solution(board, words)) {
    return true;
  }

  return false;


}

int letters_on_board(char** board) {

  int letters_on_board = 0;
  for (int r=0; r<5; r++) {
    for (int c=0; c<5; c++) {

      if (isalpha(board[r][c])) {
        letters_on_board++;
      }

    }
  }

  return letters_on_board;

}


bool recursive_solve(char** board, char** words) {

  int row, col;
  //base case return true if valid solution
  if (valid_solution(board, words)) {
    return true;
  }

  //return false if not valid solution and there are no empty squares
  if (!get_position(board, '.', row, col)) {
    return false;
  }

  for (char ch = 'A'; ch< 'Z'; ch++) {
    if (is_letter_on_board(board, ch)) {
      continue;
    }
    board[row][col] = ch;
    if (recursive_solve(board, words)) {
      return true;
    } else {
      //go try a different character in that square.
      continue;
    }
  }

  board[row][col] = '.';
  
  return false;

}

bool is_letter_on_board(char** board, char letter) {

  for (int r=0; r<5; r++) {
    for (int c=0; c<5; c++) {

      if (board[r][c] == letter) {
        return true;
      }


    }
  }

  return false;

}







