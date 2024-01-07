#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>

using namespace std;

#include "dictionary.h"
#include "doublets.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* Looks up a given word in the dictionary of approved words. 
   Returns true if the word is in the dictionary.
   Otherwise returns false. */

bool dictionary_search(const char *word) {
  static Dictionary dictionary("words.txt");
  return dictionary.search(word);
}

/* add your function definitions here */

bool find_chain_recursive(const char* start_word, const char* target_word, const char* answer_chain[], int max_steps, const char* final[], int current_step = 0);
bool in_chain(const char* chain[], const char* word);

// Question 1
bool valid_step(const char* current_word, const char* next_word) {

   //each must be formed by substituting one letter from the same place
   int number_of_changes = 0;

   int index = 0;
   while (current_word[index] != '\0' && next_word[index] != '\0') {

      if (current_word[index] != next_word[index]) {
         number_of_changes++;
      }
      index++;
   }

   if (
   number_of_changes == 1 && dictionary_search(current_word) && 
   dictionary_search(next_word) && 
   strlen(current_word) == strlen(next_word)
   ) {
      //look in glossary
         return true;
   }

   //links must be found in the glossary
   return false;

}

// Question 2
bool display_chain(const char *chain[], ostream& out) {

   int index = 0;
   int lower_case_index = 0;
   char lower_case[512];
 
   while (chain[index] != NULL) {

      strcpy(lower_case, "");

      if (index>0 && chain[index+1] != NULL) {
         
         strcpy(lower_case, chain[index]);

         lower_case_index = 0;
         while (lower_case[lower_case_index] != '\0') {
            lower_case[lower_case_index] = tolower(lower_case[lower_case_index]);
            lower_case_index++;
         }
         lower_case[lower_case_index] = '\0';

         out << lower_case << endl;
      } else {
         out << chain[index] << endl;
      }
      
      if (out.fail()) {
         return false;
      }

      index++;

   }

   return true;

}

// Question 3
//checks an input chain to see if it is valid.
bool valid_chain(const char *chain[]) {

   // rule two and 4 checked by valid_step.
   // perform valid_step on adjacent words. 
   int index = 0;

   while (chain[index + 1] != NULL) {

      if (!valid_step(chain[index], chain[index+1])) {
         return false;
      }

      // must not contain word twice over. 
      if (index > 1 && !strcmp(chain[index-1], chain[index+1])) {
         return false;
      }

      index++;

   }
   
   if (index <= 1) {
      return false;
   }

   return true;
}

// Question 4

bool find_chain(const char* start_word, const char* target_word, const char* answer_chain[], int max_steps) {

   const char* initial_answer_chain[100];
   for (int i=0; i<100; i++) {
      initial_answer_chain[i] = NULL;
   }

   return find_chain_recursive(start_word, target_word, initial_answer_chain, max_steps, answer_chain);

}

bool find_chain_recursive(const char* start_word, const char* target_word, const char* answer_chain[], int max_steps, const char* final[], int current_step) {

   char proposed_word[512];

   //base case 

   if (max_steps == 0) {

      if (!strcmp(start_word, target_word)) {

         int index = 0;
         while (answer_chain[index] != NULL) {
            index++;
         }
         answer_chain[index++] = start_word;
         answer_chain[index] = NULL;

         int index1 = 0;
         while (answer_chain[index1] != NULL) {
            final[index1] = answer_chain[index1];
            index1++;
         }
         final[index1] = NULL;

         // display_chain(answer_chain, cout);

         return true;

      } else {

         return false;

      }

   }

   const char* new_answer_chain[100];
   int index=0;
   
   while (answer_chain[index] != NULL) {
      new_answer_chain[index] = answer_chain[index];
      index++;
   }
   new_answer_chain[index++] = start_word;
   new_answer_chain[index] = NULL;

   
   //find a new word
   for (int i=0; i<strlen(start_word); i++) {

      strcpy(proposed_word, "");
      strcpy(proposed_word, start_word);

      for (char ch = 'A'; ch<='Z'; ch++) {

         proposed_word[i] = ch;

         //if its a valid step and the word is not in the chain already.
         if (valid_step(start_word, proposed_word) && !in_chain(new_answer_chain, proposed_word)) {

            if (find_chain_recursive(proposed_word, target_word, new_answer_chain, max_steps-1, final, current_step +1)) {

               return true;
            }

         }

      }
   }

   return false;


}

bool in_chain(const char* chain[], const char* word) {

   int index=0;
   while (chain[index] != NULL) {
      if (chain[index] == word) {
         return true;
      }
      index++;
   }

   return false;

}