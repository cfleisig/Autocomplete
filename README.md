# Autocomplete
## Project Description
This program quickly retrieves the top terms that match a query string and applies concepts such as binary search and lexicographic ordering.

## Programming Techniques/Skills
* binary search
* text-processing
* sorting with qsort

## How to run C code
In terminal type `gcc main.c functions.c -o autocomplete` to create executable file. Then `./autocomplete` to run the C program.

Note that as a mac user my terminal uses Z Shell (zsh), however if you use a differnet shell, these commands will likely not work for you.

## Libraries Used
* `<stdio.h>`
* `<string.h>`
* `<stdlib.h>`

## Project Files
* `main.c` This file contains the main function which is currently running tests to ensure the program is working as expected. The user may input code in the main function to determine autocomplete results for different query strings.
* `functions.c` This file contains the functions used to operate this program.
* `autocomplete.h` This file declares the funcitons and structs used in the main file.
* `cities.txt`, `wiktionary.txt` These files contain data on search queries, orderered from most searched terms to least searched terms.
    * The first line of the file indicates the number of terms
    * Each of the following lines contains data on a search term, ordered from most searched term, to least searched term
    * The number on the left of the line indicates the number of times that term has been queried by other users, also called the weight
    * The word on the right of the line is the search term

## Strucures Used
### struct term
* Purpose: to store height, width and image in a single neat structure in memory
* Defined in file: c_img.h
* Construction:
```
struct term{
    char term[200]; // contains a search term and assumes search terms are not longer than 200
    double weight; // contains the number of times the term has been searched in the past
};
```

## How to use program
In the main function found in the `main.c` file, enter the following lines of code.
1. Read in terms from a file formated like `cities.txt`
```
struct term *terms; // points to an address in memory at the start of a block of term structs in lexiographic order, each of which represents one of the terms in the .txt file
int nterms; // contains the number of terms in the .txt file
read_in_terms(&terms, &nterms, "cities.txt"); // note that "cities.txt" can be exchanged with any other file in the same format
```
2. Find autocomplete matches to a querry string, in order of most likely to least likely result, using autocomplete program
```
struct term *answer; 
int n_answer; // contains the number of matches to the querry string in order of weights
autocomplete(&answer, &n_answer, terms, nterms, "Toro");
```
3. Print autocomplete matches from most likely match to least likely match (in order of weights)
```
for (int i = 0; i < n_answer; i++){
     printf("%s\n", i, answer[i].term);
}
```

## How this code works
1. Reads in the entire file of terms, and sort the terms in lexicographic ordering. This sorted list will be reused for multiple queries.
2. Uses binary search to find the location of the first term in lexicographic ordering that matches the query string, as well as the last term in lexicographic oredering that matches the query string.
3. Extracts the terms that match the query string, and sort them by weight.
4. Extracts the top matching terms by weight

## Credits
Credit: the assignment was designed by Kevin Wayne, and adapted to C by Michael Guerzhoy.
