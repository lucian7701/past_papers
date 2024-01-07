enum Direction {N, S, W, E, NE, NW, SE, SW, INVALID_DIRECTION};

/* error codes for Question 3 */
#define ERROR_START_STATION_INVALID -1 
#define ERROR_ROUTE_ENDPOINT_IS_NOT_STATION -2
#define ERROR_LINE_HOPPING_BETWEEN_STATIONS -3
#define ERROR_BACKTRACKING_BETWEEN_STATIONS -4
#define ERROR_INVALID_DIRECTION -5
#define ERROR_OFF_TRACK -6
#define ERROR_OUT_OF_BOUNDS -7

/* pre-supplied function to load a tube map from a file*/
char **load_map(const char *filename, int &height, int &width);

/* pre-supplied function to print the tube map */
void print_map(char **m, int height, int width);

/* pre-supplied helper function to describe errors for Question 3 */
const char *error_description(int code);

/* presupplied helper function for converting string to Direction enum */
Direction string_to_direction(const char *token);

// Question 1
// given a symbol character target finds the coordinates (r,c)
// of the first occurrence of that symbol on an ASCII map with
// height rows and width columns when scanned in a row-by-row
// fashion. If the symbol is found, the function should return true
// and set the output parameters r (the row number) and c (the
// column number), both of which are indexed starting from 0. If
// the symbol cannot be found, the function should return false and
// r and c should both be set to -1.
bool get_symbol_position(char** map, int height, int width, char target, int& r, int& c);


// Question 2
// given the input parameter name describing the name of a station
// or line, returns the corresponding map symbol character. If there
// is no such station or line, return the space character ’ ’.
char get_symbol_for_station_or_line(const char* name);

// Question 3
// given the name of an origin station
// start station and string route describing a passenger journey
// in terms of the direction taken on the ASCII Tube map at each
// journey step, determines if the route is valid.
// If the route is valid the function should return the number of line
// changes required to complete the journey as the return value of
// the function, and assign the output parameter destination to
// be the name of the station at the end of the route. If the route is
// invalid, the function should return an appropriate error code.
int validate_route(char** map, int height, int width, const char* start_station, const char* route, char destination[512]);