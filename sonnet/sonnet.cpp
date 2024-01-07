#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
#include <map>
#include <string>
#include <fstream>

using namespace std;

#include "sonnet.h"

void get_phonetic_ending(const char* word, char phonetic_ending[], char buffer[]);

/* PRE-SUPPLIED HELPER FUNCTIONS START HERE */

/* NOTE: It is much more important to understand the interface to and
   the "black-box" operation of these functions (in terms of inputs and
   outputs) than it is to understand the details of their inner working. */

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int word_number, char *output_word) {
  char *output_start = output_word;
  int words = 0;

  if (word_number < 1) {
    *output_word = '\0';
    return false;
  }
  
  do {
    while (*input_line && !isalnum(*input_line))
      input_line++;

    if (*input_line == '\0')
      break;

    output_word = output_start;
    while (*input_line && (isalnum(*input_line) || *input_line=='\'')) {
      *output_word = toupper(*input_line);
      output_word++;
      input_line++;
    }
    *output_word = '\0';

    if (++words == word_number)
      return true;

  } while (*input_line);

  *output_start = '\0';
  return false;
}

/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */

char rhyming_letter(const char *ending) {

  // the next rhyming letter to be issued (persists between calls)
  static char next = 'a';
  // the table which maps endings to letters (persists between calls)
  static map<string, char> lookup;

  // providing a way to reset the table between poems
  if (ending == RESET) {
    lookup.clear();
    next = 'a';
    return '\0';
  }

  string end(ending);

  // if the ending doesn't exist, add it, and issue a new letter
  if (lookup.count(end) == 0) {
    lookup[end]=next;
    assert(next <= 'z');
    return next++;
  }

  // otherwise return the letter corresponding to the existing ending
  return lookup[end];
}

/* START WRITING YOUR FUNCTION BODIES HERE */

// Question 1

int count_words(const char* line) {

  int number_of_words = 1;
  bool is_valid;

  char output_word[512];

  do {

    if (is_valid = get_word(line, number_of_words, output_word)) {
      number_of_words++;
    }

  } while (is_valid == true);

  return number_of_words - 1;

}

// Question 2
bool find_phonetic_ending(const char* word, char phonetic_ending[]) {

  //construct the ending for the uppercase word contained in word. 
  ifstream in;
  in.open("dictionary.txt");


  //set the output parameters to be a string made up of the 
  //last two letters of the last word in the input line.

  char buffer[512];
  bool found = false;
  char buffer_word[512];
  int vowel_position = 0;

  while (!in.eof() && !found) {


    in.getline(buffer, 511);

    if (get_word(buffer, 1, buffer_word)) {
      if (!strcmp(buffer_word, word)) {
        found = true;
        
        in.close();

        get_phonetic_ending(word, phonetic_ending, buffer);
        
        return true;

      }
    }

  }

  in.close();

  return false;

}

char vowels[5] = {'A', 'E', 'I', 'O', 'U'};

//returns where the last vowel is and sets the position of the last vowel.
void get_phonetic_ending(const char* word, char phonetic_ending[], char buffer[]) {

  int index = strlen(word);
  int vowel_index = index;

  while (buffer[index] != '\0') {

    for (int i=0; i<5; i++) {
      if (buffer[index]==vowels[i]) {
        vowel_index = index;
      }
    }

    index++;

  }

  int phonetic_index = 0;
  while (buffer[vowel_index] != '\0') {

    if (buffer[vowel_index] == ' ') {
      vowel_index++;
      continue;
    }

    phonetic_ending[phonetic_index] = buffer[vowel_index];

    vowel_index++;
    phonetic_index++;

  }
  phonetic_ending[phonetic_index] = '\0';

}

bool find_rhyme_scheme(const char* filename, char scheme[]) {

  ifstream in;
  in.open(filename);

  if (in.fail()) {
    return false;
  } 


  in.close();


}