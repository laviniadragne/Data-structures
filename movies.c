#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashtable.h"
#include "Hashtable.c"
#include "LinkedList.c"
#include "LinkedList.h"

struct movie {
    char *nume;
    int an;
    char *regizor;
    int rating;
};

void print_movie(struct movie *m_info) {

    if (m_info == NULL) {
        printf("Film inexistent!\n");
        return;
    }
    printf("* Nume: %s | ", m_info->nume);
    printf("An: %d | ", m_info->an);
    printf("Regizor: %s | ", m_info->regizor);
    printf("Rating: %d\n", m_info->rating);
}

void print_hash(struct Hashtable *ht) {

    if (ht == NULL) {printf("Nu exista hashtable-ul!"); return;}
    for (int i = 0; i < ht->hmax; i++) {
        struct Node *curr = ht->buckets[i].head;
        while(curr != NULL){
            // datele despre film
            struct movie *info_movie = ((struct info *)curr->data)->value;
            print_movie(info_movie);
            curr = curr->next;
        }
    }
}
int main() {

    struct Hashtable *ht_movies;
    struct movie informatii_movie[8];
    struct movie *p_infomovie;

    /* Initializare structuri informatii movie */
    informatii_movie[0].nume = "Being Human";
    informatii_movie[0].an = 1994;
    informatii_movie[0].regizor = "Bill Forsyth";
    informatii_movie[0].rating = 1;

    informatii_movie[1].nume = "Being human";
    informatii_movie[1].an = 2008;
    informatii_movie[1].regizor = "James Cameron";
    informatii_movie[1].rating = 2;

    informatii_movie[2].nume = "Avatar";
    informatii_movie[2].an = 2009 ;
    informatii_movie[2].regizor = "James Cameron";
    informatii_movie[2].rating = 3;

    informatii_movie[3].nume = "The edge of seventeen";
    informatii_movie[3].an = 2016 ;
    informatii_movie[3].regizor ="Kelly Fremon Craig" ;
    informatii_movie[3].rating = 5;

    informatii_movie[4].nume = "Twilight";
    informatii_movie[4].an = 1998;
    informatii_movie[4].regizor = "Robert Benton";
    informatii_movie[4].rating = 10;

    informatii_movie[5].nume = "Edge of Fear";
    informatii_movie[5].an = 2018;
    informatii_movie[5].regizor = "Bobby Roth";
    informatii_movie[5].rating = 15;

    informatii_movie[6].nume = "Twilight";
    informatii_movie[6].an = 2008;
    informatii_movie[6].regizor = "Catherine Hardwicke";
    informatii_movie[6].rating = 6;

    informatii_movie[7].nume = "The edge of love";
    informatii_movie[7].an = 2008;
    informatii_movie[7].regizor = "John Maybury";
    informatii_movie[7].rating = 2;

    // task-ul 1


    char nume_film[30], nume_regizor[30];
    // aloc hashtable de movies si il initializez
    ht_movies = malloc(sizeof(struct Hashtable));
    init_ht(ht_movies, 10, hash_function_string, compare_function_strings);

    //adaug rand pe rand filme in hashtable, folosind ca si key numele filmului
    put(ht_movies, "Being Human", strlen("Being Human") + 1, &informatii_movie[0]);
    put(ht_movies, "Being human", strlen("Being human") + 1, &informatii_movie[1]);
    put(ht_movies, "Avatar", strlen("Avatar") + 1, &informatii_movie[2]);
    put(ht_movies, "The edge of seventeen", strlen("The edge of seventeen") + 1, &informatii_movie[3]);
    put(ht_movies, "Twilight", strlen("Twilight") + 1, &informatii_movie[4]);
    put(ht_movies, "Edge of Fear", strlen("Edge of Fear") + 1, &informatii_movie[5]);
    put(ht_movies, "The edge of love", strlen("The edge of love") + 1, &informatii_movie[7]);
    put(ht_movies, "Twilight2", strlen("Twilight2") + 1, &informatii_movie[6]);


    // task 2


    // citesc numele unui film
    fgets(nume_film,30,stdin);
    nume_film[strlen(nume_film)-1] = '\0';
    // caut dupa nume filmul in dictionar
    p_infomovie = get(ht_movies, nume_film);
    // daca l-am gasit pe o anumita pozitie in dictionar, verific daca este chiar acela
    if(p_infomovie!= NULL && strcmp(nume_film, p_infomovie->nume) == 0){
            print_movie(p_infomovie);
    }
    // altfel nu exista filmul in dictionar
    else printf("Nu exista filmul!\n");
    

    // task 3


    int gasit = 0;
    // citesc un nume de regizor
    fgets(nume_regizor,30,stdin);
    nume_regizor[strlen(nume_regizor)-1] = '\0';
    // parcurg structura de informatii de filme
    for (int i = 0; i < 8; i++) {
        // caut regizorul
        if(strcmp(informatii_movie[i].regizor, nume_regizor) == 0) {
                // caut filmul respectiv daca se afla in dictionar, pe baza numelui
                int yes = has_key (ht_movies, informatii_movie[i].nume);
                // daca n-am gasit filmul in dictionar, inseamna ca nu exista nici regizorul in dictionar, adaugat
                if  (yes == 0) printf("Never heard about him\n");
                else {
                    // daca exista in dictionat il caut si afisez informatii despre filmele acelui regizor
                    p_infomovie = get(ht_movies, informatii_movie[i].nume);
                    print_movie(p_infomovie);
                }
            gasit = 1;
        }
    }
        // daca nu l-am gasit deloc, inseamna ca el nu este nici in lista de structuri informatii movies
    if(gasit == 0) printf("Nu exista acest regizor in array!\n");


    // task 4


    // parcurg lista de informatii movies
    for(int i = 0; i < 8; i++){

        // pentru fiecare film pentru care are am informatii il caut in dictionar
        p_infomovie = get(ht_movies, informatii_movie[i].nume);
        // daca il gasesc in dictionar
        if(p_infomovie!=NULL) {
            // ii compar rating-ul cu 5
            if(5 > p_infomovie->rating) {

                // afisez ce film sterg si il sterg din hashtable, folosind numele ca si key
                printf("Am sters filmul %s !\n", p_infomovie->nume);
                remove_ht_entry(ht_movies, informatii_movie[i].nume);
            }
        }
    }

    // printez hashtable-ul si eliberez memoria alocata lui
    print_hash(ht_movies);
    free_ht(ht_movies);

    return 0;
 }
