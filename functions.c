#include "autocomplete.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int compare_lexi(const void *p, const void *q){
    struct term *a = (struct term *)p;
    struct term *b = (struct term *)q;

    return strcmp(a -> term, b -> term);
}

int compare_weight(const void *p, const void *q){
    struct term *a = (struct term *)p;
    struct term *b = (struct term *)q;

    return (b -> weight) - (a -> weight);
}

void read_in_terms(struct term **terms, int *pnterms, char *filename){
    /* Takes in a pointer to a pointer to struct term, a pointer to an int, and the name of a file that is formatted like cities.txt
    
    Allocates memory for all the terms in the file and stores a pointer to the block in *terms. 
    Stores the number of terms in int *pnterms.
    Reads in all the terms from filename, and places them in the block pointed to by *terms. */

    FILE *fp = fopen(filename, "r"); //opens file to read

    if (fp == NULL){
        printf("Error opening file\n");
        exit(1);
    }
    
    fscanf(fp, "%d", pnterms); //retreives number of terms
    *terms = malloc(sizeof(struct term) * (*pnterms)); //allocates array of struct terms

    if (*terms == NULL){
        printf("Error allocating memory\n");
        exit(1);
    }

    //iterates through line by line
    for (int i = 0; i < *pnterms; i++) 
    {
        fscanf(fp, "%lf", &((*terms)[i].weight)); //retreives weight 
        fgetc(fp); //removes tab/spaces after weight
        fscanf(fp, "%200[^\n]", (*terms)[i].term); //retreives term string
    }
    
    fclose(fp); //closes file

    //puts array in lexicographic order
    qsort(*terms, *pnterms, sizeof(struct term), compare_lexi);
}

int lowest_match(struct term *terms, int nterms, char *substr) {
    //Returns the index in terms of the first term in lexicographic ordering that matches the string substr.
    //This function must run in O(log(nterms)) time, where nterms is the number of terms in terms.
    //Assume that terms is sorted in ascending lexicographic ordering.

    //find length of substring
    int l_substr;
    for (l_substr = 0; substr[l_substr] != '\0'; l_substr++);
    //printf("l_substr = %d\n", l_substr);

    //initialize indices
    int i1 = 0;
    int i2 = (nterms - 1)/2;
    int i3 = nterms - 1;

    //binary search for lowest value
    while(strncmp(terms[i1].term, substr, l_substr) != 0 && i1 < i3){
        
        //printf("terms[%d]: %s\t terms[%d]: %s\t terms[%d]: %s\n", i1, terms[i1].term, i2, terms[i2].term, i3, terms[i3].term);
        
        if (i1 + 1 == i3){
            i1 = i3;
        } else if(strncmp(substr, terms[i2].term, l_substr) <= 0){
            i3 = i2;
            i2 = (i3 + i1)/2;
        } else if (strncmp(terms[i2].term, substr, l_substr) < 0) {
            i1 = i2;
            i2 = (i3 + i1)/2;
        }
    }

    //printf("\nterms[%d]: %s\n\n", i1, terms[i1].term);

    if(strncmp(terms[i1].term, substr, l_substr) == 0){
        return i1;
    } else {
        printf("Error value not found\n");
        return 0;
    }

    return 0;
}

int highest_match(struct term *terms, int nterms, char *substr){
    //Returns the index in terms of the last term in lexicographic ordering that matches the string substr.
    //This function must run in O(log(nterms)) time, where nterms is the number of terms in terms.
    //Assume that terms is sorted in ascending lexicographic ordering.

    //find length of substring
    int l_substr;
    for (l_substr = 0; substr[l_substr] != '\0'; l_substr++);
    //printf("l_substr = %d\n", l_substr);

    //initialize indices
    int i1 = 0;
    int i2 = (nterms - 1)/2;
    int i3 = nterms - 1;

    //binary search for lowest value
    while(strncmp(terms[i3].term, substr, l_substr) != 0 && i1 < i3){
        
        //printf("terms[%d]: %s\t terms[%d]: %s\t terms[%d]: %s\n", i1, terms[i1].term, i2, terms[i2].term, i3, terms[i3].term);
        
        if (i1 + 1 == i3){
            i3 = i1;
        } else if(strncmp(substr, terms[i2].term, l_substr) < 0){
            i3 = i2;
            i2 = (i3 + i1)/2;
        } else if (strncmp(terms[i2].term, substr, l_substr) <= 0) {
            i1 = i2;
            i2 = (i3 + i1)/2;
        }
    }

    //printf("\nterms[%d]: %s\n\n", i1, terms[i1].term);

    if(strncmp(terms[i3].term, substr, l_substr) == 0){
        return i1;
    } else {
        printf("Error value not found\n");
        return 0;
    }

    return 0;
}

void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr){
    //Takes terms (assume it is sorted lexicographically), the number of terms nterms, the query string substr
    //Places the answers in answer, with *n_answer being the number of answers. The answer should be sorted by weight.

    //use lowest_match and highest_match to find n_answers
    int lowest = lowest_match(terms, nterms, substr);
    int highest = highest_match(terms, nterms, substr);
    *n_answer = highest - lowest + 1;

    //malloc answers an array of struct terms
    *answer = malloc(sizeof(struct term) * (*n_answer));
    if (*answer == NULL){
        printf("Error allocating memory\n");
        exit(1);
    }

    //loop through answer terms and put in malloced array
    for (int i = lowest; i <= highest; i++) {
        strcpy((*answer)[i - lowest].term, terms[i].term);
        (*answer)[i - lowest].weight = terms[i].weight;
    }
    
    //use qsort to sort array by weight
    qsort(*answer, *n_answer, sizeof(struct term), compare_weight);
}

//gcc main.c functions.c -o test