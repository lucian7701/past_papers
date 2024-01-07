// RESET is a constant used by function rhyming_letter(...)
#define RESET NULL

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int number, char *output_word);

/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */

char rhyming_letter(const char *ending);


// Question 1
/* returns the number of words in a given input string line. */
int count_words(const char* line);

// Question 2
/* uses the phonetic dictionary in the file dictionary.txt to
construct the phonetic ending for the (uppercase) word contained
in the input parameter word. If this word is in the phonetic dic-
tionary, the corresponding phonetic ending should be stored in
the output parameter phonetic ending, and the function should
return true. Otherwise the function should return false. */
bool find_phonetic_ending(const char* word, char phonetic_ending[]);

// Question 3
/* produces in the output parameter scheme the rhyme scheme for
the sonnet contained in the file filename. If the file does not exist,
the function should return false; otherwise the function should
return true. */
bool find_rhyme_scheme(const char* filename, char scheme[]);