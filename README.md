# Autocomplete
## Project Description
This program quickly retrieves the top terms that match a query string and applies concepts such as binary search and lexicographic ordering.

## Programming Techniques/Skills
* binary search
* lexiographic ordering
* text-processing

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
* `cities.txt`, `wiktionary.txt` These files 

## Strucures Used
### struct term
* Purpose: to store height, width and image in a single neat structure in memory
* Defined in file: c_img.h
* Construction:
```
struct term{
    char term[200]; // assume terms are not longer than 200
    double weight;
};
```

## How this code works

    ```
## Credits
Credit: the assignment was designed by Kevin Wayne, and adapted to C by Michael Guerzhoy.
