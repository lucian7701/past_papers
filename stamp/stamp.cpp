#include <iostream>
#include <openssl/sha.h>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <fstream>
#include "stamp.h"
#include <cctype>

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

bool isHexidecimal(const char* digest);
void count_to_chars(char* count_chars, int count);

// helper function for internal use only
// transforms raw binary hash value into human-friendly hexademical form
void convert_hash(const unsigned char *str, char *output, int hash_length) {
  char append[16];
  strcpy (output, "");
  for (int n=0; n<hash_length; n++) {
    sprintf(append,"%02x",str[n]);
    strcat(output, append);
  }
}

// pre-supplied helper function
// generates the SHA1 hash of input string text into output parameter digest
// ********************** IMPORTANT **************************
// ---> remember to include -lcrypto in your linking step <---
// ---> so that the definition of the function SHA1 is    <---
// ---> included in your program                          <---
// ***********************************************************
void text_to_SHA1_digest(const char *text, char *digest) {
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1( (const unsigned char *) text, strlen(text), hash);
  convert_hash(hash, digest, SHA_DIGEST_LENGTH);
}

/* add your function definitions here */
// Question 1
int leading_zeros(const char* digest) {

  if (!isHexidecimal(digest)) {
    return -1;
  }

  int zero_count = 0;
  for (int i=0; i<5; i++) {

    if (digest[i] == '0') {
      zero_count++;
    } else {
      return zero_count;
    }
  }

return zero_count;
}

//check if all characters are valid hexadecimal digits.
bool isHexidecimal(const char* digest) {

  for (int i=0; i<strlen(digest); i++) {
    if (!isalnum(digest[i])) {
      return false;
    }
    if (isalpha(digest[i]) && !islower(digest[i])) {
      return false;
    }
  }

  return true;

}

//Question 2
bool file_to_SHA1_digest(const char* filename, char* digest) {

  //convert the file to digest
  char buffer[100000];

  //open the file
  ifstream in;
  in.open(filename);

  //if file can not be opened set the digest to error.
  if (in.fail()) {
    strcpy(digest, "error");
    in.close();
    return false;
  }

  char my_char;

  int i = 0;
  //set digest to digest of file
  in.get(my_char);
  while (!in.eof()) {
    buffer[i]=my_char;
    in.get(my_char);
    i++;
  }

  buffer[i] = '\0';

  // cout << buffer << endl;

  text_to_SHA1_digest(buffer, digest);
  
  
  in.close();
  
  return true;

}


// Question 3
bool make_header(const char* recipient, const char* filename, char* header) {
  
  char digest[41];
  strcpy(digest, "");

  //look into this!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //get the hash of the message, return false if not possible
  // if (file_to_SHA1_digest("message1.txt", digest)) {
  //   cout << digest << endl;
  // }

  bool success = file_to_SHA1_digest(filename, digest);
  
  if (!success) {
    return false;
  }

  header[0]='\0';


  //compile the header together in appropriate form. use strcat. 
  strcpy(header, recipient);
  strcat(header, ":");
  strcat(header, digest);
  strcat(header, ":");

  char header_no_count[512];
  strcpy(header_no_count, header);

  char count_chars[8];
  int count_index = strlen(header);

  //for 10million attempts, incrementing counter
  //hash the file and see if there are 5 leading zeros/valid has. 
  for (int count=0; count <= 10000000; count++) {
    
    strcpy(count_chars, "");
    strcpy(digest, "");

    count_to_chars(count_chars, count);
    strcat(header, count_chars);

    // cout<< header << endl;

    text_to_SHA1_digest(header, digest);
  
      if (leading_zeros(digest) == 5) {
        
        return true;
      }
    
    strcpy(header, header_no_count);
     
  }

  return false;

}

int number_of_digits(int number) {
  int digits = 0;
  if (number == 0) {
    return 1;
  }
  while (number !=0) {
    number /= 10;
    digits++;
  }
  
  return digits;
}

void count_to_chars(char* count_chars, int count) {

  int digits = number_of_digits(count);

  count_chars[digits] = '\0';
  
  for (int i=digits-1; i>=0; i--) {
    count_chars[i] = (count%10) + '0';
    count/=10;
  }

}


// Question 4
MessageStatus check_header(const char* email_address, const char* header, const char* filename) {

  //see that the header digest has 5 0s
  char digest[41];
  strcpy(digest, "");
  //hash the header. 
  text_to_SHA1_digest(header, digest);


  //if not return invalid header digest
  if (leading_zeros(digest) < 5) {
    return INVALID_HEADER_DIGEST;
  }

  //split header into 2 char[].
  char email[100];
  strcpy(email, "");
  char message_hash[41];
  strcpy(message_hash, "");
  
  int index = 0;
  while (header[index] != ':') {
    email[index] = header[index];
    index++;
  }
  email[index] = '\0';
  
  index++;
  int message_index = 0;
  while (header[index] != ':') {
    message_hash[message_index] = header[index];
    index++;
    message_index++;
  }
  message_hash[message_index] = '\0';

  //see that the messaged is correctly hashed. hash the file name and ensure that this is the
  //same as the message segment of header. 
  strcpy(digest, "");
  if (!file_to_SHA1_digest(filename, digest)) {
    return INVALID_MESSAGE_DIGEST;
  }

  if (strcmp(digest, message_hash)) {
    return INVALID_MESSAGE_DIGEST;
  }

  // see that the email is correct. Compare email in header to email passed. 
  if (strcmp(email, email_address)) {
    return WRONG_RECIPIENT;
  }




  return VALID_EMAIL;


}














