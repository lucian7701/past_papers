#ifndef PLAYFAIR_H
#define PLAYFAIR_H

void prepare(const char input_string[512], char prepared[]);

void grid(const char code_word[], char playfair[][6]);

void bigram(char square[][6], char inchar1, char inchar2, char& outchar1, char& outchar2);

void encode(char playfair[][6], const char* prepared, char* encoded);

#endif