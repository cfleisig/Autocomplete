#include "autocomplete.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int test_read_in_terms_cities(void){
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "cities.txt");

    int error_count = 0;
    if(nterms != 93827)
        { error_count++;}
    if(terms[0].weight != (double)14608512)
        { error_count++;}
    if(strcmp(terms[0].term, "Shanghai, China") != 0)
        { error_count++; printf("passed");}
    if(terms[93826].weight != (double)2)
        { error_count++; }
    if(strcmp(terms[93826].term, "Al Khāniq, Yemen") != 0)
        { error_count++;printf("passed");}
    if(terms[45849].weight != (double)4697)
        { error_count++;}
    if(strcmp(terms[45849].term, "Onga, Hungary") != 0)
        {error_count++;}

    if(error_count == 0){
        return 0;
    } else {
        return 1;
    }
}

int test_read_in_terms_wik_lexi(void){
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "wiktionary.txt");

    int error_count = 0;
    if(nterms != 10000)
        { error_count++; printf("1passed");}
    if(terms[9999].weight != (double)630850)
        { error_count++; printf("2passed");}
    if(strcmp(terms[9999].term, "zone") != 0)
        { error_count++; printf("3passed");}
    if(terms[0].weight != (double)435598)
        { error_count++; printf("4passed");}
    if(strcmp(terms[0].term, "'cause") != 0)
        { error_count++; printf("5passed");}
    if(terms[8984].weight != (double)3012080)
        { error_count++; printf("6passed");}
    if(strcmp(terms[8984].term, "threatened") != 0)
        {error_count++; printf("7passed");}

    if(error_count == 0){
        return 0;
    } else {
        return 1;
    }
}

int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "cities.txt");
    //lowest_match(terms, nterms, "Tor");
    //highest_match(terms, nterms, "Tor");
    
    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, "Toro");

    for (int i = 0; i < n_answer; i++)
    {
        printf("answer[%d].weight = %lf\t answer[%d].term = %s\n", i, answer[i].weight, i, answer[i].term);
    }

    return 0;
}