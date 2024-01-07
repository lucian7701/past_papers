enum MessageStatus {
  INVALID_HEADER=-1,
  WRONG_RECIPIENT=-2,
  INVALID_MESSAGE_DIGEST=-3,
  INVALID_HEADER_DIGEST=-4,
  VALID_EMAIL=1
};

/* pre-supplied helper function */
/* generates the SHA1 hash of input string text into output parameter digest */
void text_to_SHA1_digest(const char *text, char *digest);

// Question 1
// takes as its parameter a hexadecimal string representing a hash digest and returns the number of leading zeros it
// beings with. If the input string contains characters that are not valid hexadecimal digits
// (i.e. ’0’ to ’9’ and ’a’ to ’f’) then the function should return -1.
int leading_zeros(const char* digest);

// Question 2
/* returns in digest the SHA1 digest of the contents of the file with name filename. 
If the file cannot be opened then the function should return false with digest set to “error”; 
otherwise return true.*/
bool file_to_SHA1_digest(const char* filename, char* digest);

// Question 3
/* prepares a header for a given email message. Here recipient is a read-only input parameter specifying
the email address of the message recipient, filename is a read-only input parameter spec-
ifying the file containing the message body, and header is an output parameter containing
the header */
bool make_header(const char* recipient, const char* filename, char* header);

// Question 4
/* three input parameters: the user’s email address, a received message header and the name of a file
containing the text of a received email body. The return value should of enumerated type
MessageStatus */
MessageStatus check_header(const char* email_address, const char* header, const char* filename);