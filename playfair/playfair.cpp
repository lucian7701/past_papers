#include <iostream>
#include <cctype>
#include <cstring>
#include "playfair.h"

using namespace std;

bool occurs_before(const char str[], char letter, int pos);

char possible_characters[37];
void getPossibleCharacters(char possible_characters[]);

void find_char_pos(char square[][6], int char_pos[], char ch);

void prepare(const char input_string[512], char prepared[]) {

    int prepared_index = 0;
    prepared[0] = '\0';

    //a for loop going through each itme of the input_string and appends alphanumeric characters to the prepared string.
    for (int i=0; i<strlen(input_string); i++) {
        
        if (strlen(prepared) < 100) {
            if (isalnum(input_string[i])) {
                prepared[prepared_index] = toupper(input_string[i]);
                prepared_index++;
                prepared[prepared_index] = '\0';
            }
        }  
    }

    if (strlen(prepared) % 2 != 0) {
            prepared[prepared_index] = 'X';
            prepared[prepared_index+1] = '\0';
    }

}


void grid(const char code_word[], char playfair[][6]) {

    //approach, concat two strings into one big string. then load each letter in one by one, only if it is not occur before. 

    getPossibleCharacters(possible_characters);
    
    char word_and_chars[strlen(code_word) + 37];
    word_and_chars[0] = '\0';

    strcat(word_and_chars, code_word);
    strcat(word_and_chars, possible_characters);

    char playfair_string[36];

    int write_index = 0;
    for (int i=0; word_and_chars[i] != '\0'; i++) {
        if (!occurs_before(word_and_chars, word_and_chars[i], i)) {
            playfair_string[write_index] = word_and_chars[i];
            write_index++;
            playfair_string[write_index] = '\0';
        }
        
    }

    // cout << playfair_string << endl;

    int index = 0;
    for (int row=0; row<6; row++) {
        for (int col=0; col<6; col++) {
            playfair[row][col] = playfair_string[index];
            index++;
        }
    }

}

bool occurs_before(const char str[], char letter, int pos) {

    for (int i=0; i<pos; i++) {
        if (str[i] == letter) {
            return true;
        }
    } 

    return false; 
}

void getPossibleCharacters(char possible_characters[]) {

    for (int i=0; i<26; i++) {
        possible_characters[i] = 'A' + i;
    }

    for (int i=26; i<36; i++) {
        possible_characters[i] = '0' + (i-26);
    }
    possible_characters[37] = '\0';

    // cout << possible_characters << endl;

}

// question 3

void bigram(char square[][6], char inchar1, char inchar2, char& outchar1, char& outchar2) {

    //this needs to find inchar1 and inchar2 in the square, and then find the appropriate values. 
    //outchar1 is the character at the row of the first bigram and the column of the second. 
    //outchar2 is the character at the column of the first bigram and the row of the second.

    //first find the positions of both. This will use a for loop.
    //using these positions find the out characters.

    int char1_pos[2];
    find_char_pos(square, char1_pos, inchar1);

    int char2_pos[2];
    find_char_pos(square, char2_pos, inchar2);

    //find outchar1
    outchar1 = square[char1_pos[0]][char2_pos[1]];
    outchar2 = square[char2_pos[0]][char1_pos[1]];

    // cout << outchar1 << endl;
    // cout << outchar2 << endl;

}

void find_char_pos(char square[][6], int char_pos[], char ch) {

    for (int row=0; row<6; row++) {
        for (int col=0; col<6; col++) {
            if (square[row][col] == ch) {
                char_pos[0] = row;
                char_pos[1] = col;
            }
        }
    }
}

// question 4

// void encode(char playfair[][6], char prepared[], char encoded[]) {

//     //for each duo of characters from prepared, use bigram to get the new characters. 
//     encoded[0] = '\0';

//     //get 2 values from prepared. get their bigram output and put that into the encoded string.

//     int index = 0;
//     while (prepared[index] != '\0') {
//         char inchar1 = prepared[index++];
//         char inchar2 = prepared[index++];
//         char outchar1;
//         char outchar2;
//         bigram(playfair, inchar1, inchar2, outchar1, outchar2);
//         encoded[index - 2] = outchar1;
//         encoded[index - 1] = outchar2;
//         encoded[index] = '\0';
//     }

// }

//recursive version

void encode(char playfair[][6], const char* prepared, char* encoded) {

    //basecase

    if (strlen(prepared) <=1) {
        *encoded = '\0';
        return;
    }

    char out1, out2;
    bigram(playfair, prepared[0], prepared[1], out1, out2);

    encoded[0] = out1;
    encoded[1] = out2;
 
    encode(playfair, prepared+2, encoded+2);

    // //for each duo of characters from prepared, use bigram to get the new characters. 
    // encoded[0] = '\0';

    // //get 2 values from prepared. get their bigram output and put that into the encoded string.

    // int index = 0;
    // while (prepared[index] != '\0') {
    //     char inchar1 = prepared[index++];
    //     char inchar2 = prepared[index++];
    //     char outchar1;
    //     char outchar2;
    //     bigram(playfair, inchar1, inchar2, outchar1, outchar2);
    //     encoded[index - 2] = outchar1;
    //     encoded[index - 1] = outchar2;
    //     encoded[index] = '\0';
    // }

}

