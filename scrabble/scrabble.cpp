#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
#include "scrabble.h"

using namespace std;

/* insert your function definitions here */

int modify_score(char tile, ScoreModifier score_modifier, int& word_multiplier);

//Question 1
int tile_score(char tile) {

    //check is alpha 
    // then convert to upper case

    if (isalpha(tile)) {
        tile = toupper(tile);
    }

    switch (tile) {
    
    case 'A':
    case 'E':
    case 'I':
    case 'L':
    case 'N':
    case 'O':
    case 'R':
    case 'S':
    case 'T':
    case 'U': return 1;
    case 'D':
    case 'G': return 2;
    case 'B':
    case 'C':
    case 'P': 
    case 'M': return 3;
    case 'F':
    case 'H':
    case 'V': 
    case 'W': 
    case 'Y': return 4;
    case 'K': return 5;
    case 'J':
    case 'X': return 8;
    case 'Q': 
    case 'Z': return 10;
    case ' ':
    case '?': return 0;
    default: return -1;

    }
}

//Question 2
bool can_form_word_from_tiles(const char* word, const char* tiles, char played_tiles[80]) {

    //for each letter in the word. doest that letter appear in tiles. if it does
    // add it to played tiles. increment the position, call the function again. 
    // cout << "it gets" << endl;
    //base case
    if (strlen(word) == 0) {
        //word can be formed. 
        return true;
    }

    // cout << word << endl;

    //for each letter of word, search tiles for that letter. if it appears, create a new word
    //and new tile without those letters
    for (int i=0; i<strlen(tiles); i++) {

        if (word[strlen(word)-1] == tiles[i]) {
            // cout << "letter matches" << tiles[i] << endl;
            //put that letter into played tiles
            // int no_played_tiles = strlen(played_tiles);
            // played_tiles[strlen(word)] = '\0';
            // played_tiles[strlen(word) -1] = tiles[i];

            

            // played_tiles[strlen(word)] = '\0';
            
            //remove letter from word
            int size_of_new = strlen(word);
            char new_word[size_of_new];
            strcpy(new_word, "");
            // memset(new_word, '\0', sizeof(new_word));
            strncpy(new_word, word, size_of_new-1);
            new_word[size_of_new-1] = '\0';
            // cout << new_word << endl;

            //remove letter from tiles
            char new_tiles[strlen(tiles)+1];
            strcpy(new_tiles, tiles);

            //remove used tile
            for (int j=i; j<strlen(tiles); j++) {
                new_tiles[j] = new_tiles[j+1];
            }

            if (can_form_word_from_tiles(new_word, new_tiles, played_tiles)) {
                played_tiles[strlen(word)-1] = tiles[i];
                played_tiles[strlen(word)] = '\0';
                return true;
            }

        }
    }

    for (int i=0; i<strlen(tiles); i++) {

        if (tiles[i] == ' ' || tiles[i] == '?') {

            // cout << "letter matches" << tiles[i] << endl;
            //put that letter into played tiles


            //remove letter from word
            int size_of_new = strlen(word);
            char new_word[size_of_new];
            strcpy(new_word, "");
            // memset(new_word, '\0', sizeof(new_word));
            strncpy(new_word, word, size_of_new-1);
            new_word[size_of_new-1] = '\0';
            // cout << new_word << endl;

            //remove letter from tiles
            char new_tiles[strlen(tiles)+1];
            strcpy(new_tiles, tiles);

            for (int j=i; j<strlen(tiles); j++) {
                new_tiles[j] = new_tiles[j+1];
            }

            if (can_form_word_from_tiles(new_word, new_tiles, played_tiles)) {
                played_tiles[strlen(word)-1] = tiles[i];
                played_tiles[strlen(word)] = '\0';
                return true;
            }

        }
    }

    strcpy(played_tiles, "");
    return false;

}

//Question 3
int compute_score(const char* played_tiles, ScoreModifier score_modifiers[]) {
    
    int score = 0;
    int word_multiplier = 1;


    //loop through each character in played tiles and score modifiers 
    //find the score of the character and apply modification approriately.
    int index = 0;
    while (played_tiles[index] != '\0') {
        score += modify_score(played_tiles[index], score_modifiers[index], word_multiplier);
        index++;
    }
    
    score*=word_multiplier;

    if (strlen(played_tiles) == 7) {
        score += 50;
    }
    // cout << "word multiplier" << word_multiplier << endl;

    return score;

}

int modify_score(char tile, ScoreModifier score_modifier, int& word_multiplier) {

    int score = tile_score(tile);

    switch (score_modifier) {

        case DOUBLE_LETTER_SCORE: return score*2;
        case TRIPLE_LETTER_SCORE: return score*3;
        case DOUBLE_WORD_SCORE: 
            word_multiplier*=2;
            return score;
        case TRIPLE_WORD_SCORE: 
            word_multiplier*=3;
            return score;
        
        default: return score;

    }

}

//Question 4
int highest_scoring_word_from_tiles(const char* tiles, ScoreModifier score_modifiers[], char word[]) {


    char dictionary_word[512];
    char test_tiles[512];

    //figure out which words in the dictionary can be made from the tiles
    ifstream in;
    in.open("words.txt");

    char played_tiles[80];
    int highest_score = 0;
    int word_score;

    while (!in.eof()) {

        strcpy(played_tiles, "");
        // strcpy(dictionary_word, "");
        strcpy(test_tiles, "");
        strcpy(test_tiles, tiles);

        in >> dictionary_word;
        // cout << dictionary_word << endl;
        //check if you can form the word from the tiles
        
        if (can_form_word_from_tiles(dictionary_word, test_tiles, played_tiles)) {
            
            word_score = compute_score(played_tiles, score_modifiers);
            
            if (word_score >50) {
                cout << played_tiles << endl;
                cout << word_score << endl;
            }
            
            if (highest_score < word_score) {
                highest_score = word_score;
                strcpy(word, dictionary_word);    
            }
        }
    }

    in.close();
    
    if (highest_score) {
       return highest_score; 
    }

    //if you can't find a word, return -1
    return -1;
}
