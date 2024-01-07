/*  This pre-supplied function looks up a given word in the dictionary
    of approved words. It is assumed that the input word is in uppercase.
    The function returns true if the word is in the dictionary.
    Otherwise returns false. */

bool dictionary_search(const char *word);

/* add your function prototypes here */

// Question 1
/* returns true if the step from
current word to next word represents a valid step in a Doublet chain according to Rule 2 and Rule 4 of
Figure 2. Assuming that both words are supplied in uppercase format */
bool valid_step(const char* current_word, const char* next_word);

// Question 2
/* writes a given chain to an
output stream according to the conventions for the presentation of chains described in the Problem
Description. The input parameter chain is a NULL-terminated array of uppercase C-style strings
representing the words found at each step of the chain, while the input parameter output stream can
be any valid output stream, including cout. The function should return true if the entire chain was
successfully written to the output stream, and false otherwise. */
bool display_chain(const char *chain[], ostream& out);

// Question 3
/* returns true if and only if the given chain is a
valid Doublets chain according to all four rules of Figure 2. The input parameter chain is a
NULL-terminated array of uppercase C-style strings representing the words found at each step of the
chain. */
bool valid_chain(const char *chain[]);

// Question 4
/* attempts to find a valid chain beginning with start word and ending with target word in up to
max steps steps. If a valid chain can be found, output parameter answer chain should contain the
found chain (in the form of a NULL-terminated array of uppercase C-style strings) and the function
should return true. Otherwise the function should return false. */
bool find_chain(const char* start_word, const char* target_word, const char* answer_chain[], int max_steps);