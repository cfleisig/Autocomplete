#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct term{
    char term[200]; // assume terms are not longer than 200
    double weight;
};

int compare_lexi(const void *p, const void *q){
    struct term *a = (struct term *)p;
    struct term *b = (struct term *)q;

    return strcmp(a -> term, b -> term);
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
        fscanf(fp, "%200[^\n]\n", (*terms)[i].term); //retreives term string
    }
    
    fclose(fp); //closes file

    //puts array in lexicographic order
    qsort(*terms, *pnterms, sizeof(struct term), compare_lexi);
}

int lowest_match(struct term *terms, int nterms, char *substr) {
    //Returns the index in terms of the first term in lexicographic ordering that matches the string substr.
    //This function must run in O(log(nterms)) time, where nterms is the number of terms in terms.
    //Assume that terms is sorted in ascending lexicographic ordering.

    int l_substr;
    for (l_substr = 0; l_substr[i] != '\0'; l_substr++);
    
    printf("l_substr = %d\n", l_substr);
    return 0;
}

int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "b_r.txt");
    /*
    printf("\nnterms: %d\n\n", nterms);
    for (int i = 0; i < nterms; i++)
    {
        printf("terms[%d].weight: %lf\t terms[%d].term: %s\n", i, terms[i].weight, i, terms[i].term);
    }
    */

    //Returns the index in terms of the first term in lexicographic ordering that matches the string substr.
    //This function must run in O(log(nterms)) time, where nterms is the number of terms in terms.
    //Assume that terms is sorted in ascending lexicographic ordering.
    //int lowest_match(struct term *terms, int nterms, char *substr)
    
    //printf("strcmp: %d\n", strcmp("abc", "bcd")); -> -1
    
    /*char substr[15] = "Guli, China ";

    const int l_substr = sizeof(substr)/sizeof(char);

    int i1 = 0;
    int i2 = (nterms - 1)/2;
    int i3 = nterms - 1;

    while(strncmp(terms[i1].term, substr, l_substr) != 0 && i1 < i3){
        
        printf("terms[%d]: %s\t terms[%d]: %s\t terms[%d]: %s\n", i1, terms[i1].term, i2, terms[i2].term, i3, terms[i3].term);
        
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
    printf("\nterms[%d]: %s\n\n", i1, terms[i1].term); */

    lowest_match(terms, nterms, "Ham");

    return 0;
}