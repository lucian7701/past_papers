enum ScoreModifier { NONE, DOUBLE_LETTER_SCORE, TRIPLE_LETTER_SCORE, DOUBLE_WORD_SCORE, TRIPLE_WORD_SCORE };

/* insert your function prototypes here */

//Question 1 
/* returns the tile score for a given tile. Here tile is an input parameter of character type. 
If tile is a letter (whether uppercase or lowercase) then the function should return the tile score for 
that letter. If tile is ' ' or '?' (both of which can be used to represent the blank tile), 
the function should return 0. Otherwise the function should return -1.*/
int tile_score(char tile);

//Question 2
/* word is an input type describing the target word while tiles is an 
input parameter of string type parameter of string
describing the tiles in the collection. You may assume that the target word is a valid English word. If
the target word can be formed from the tiles according to the rules described in the Problem Description,
the function should return true, and output parameter played_tiles should be a null-terminated string
consisting of the ordered collection of tiles used. Otherwise the function should return false. */
bool can_form_word_from_tiles(const char* word, const char* tiles, char played_tiles[80]);

//Question 3
/* returns the word score given a played_tiles string and an array of score_modifiers. 
The individual elements in the score_modifiers array are of enumerated type ScoreModifier. */
int compute_score(const char* played_tiles, ScoreModifier score_modifiers[]);

//Question 4
/* returns the highest word score that can be achieved given a particular collection of tiles and score
modifiers, using any of the words in the supplied dictionary. Here tiles and score_modifiers are input
parameters of type string and ScoreModifier[] respectively.
If it not possible to make any word in the supplied dictionary from the tiles then the function should
return -1. Otherwise output parameter word should contain the word attaining the highest word score,
and the function should return the achieved word score.*/
int highest_scoring_word_from_tiles(const char* tiles, ScoreModifier score_modifiers[], char word[]);