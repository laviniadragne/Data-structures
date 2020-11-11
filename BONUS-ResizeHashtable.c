
/* TestHashtable.c
 * Alexandru-Cosmin Mihai
 */
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

// functie de redimensionare a unui hashtable
// in functie de o toleranta pe care o stabilesc in prealabil, hashtable-ul va fi redimensionat;
// aloc un nou array de liste, cu o dimensiune dubla de buckets; copiez nod cu nod informatia
// din hashtable, in noul array si mut pointer-ul de la vechiul array la noul array
// redimensionat; apoi eliberez memoria alocata vechiului array de liste din hashtable
void resize (struct Hashtable *ht) {

    // calculez toleranta de la care trebuie sa redimensionez array-ul
    float tol = (float)ht->size/(float) ht->hmax;
    // daca toleranta este mai mare decat o valoare pe care o stabilesc eu
    if(tol > 0.3) {

        // declar si aloc memorie pentru un array de liste copie, cu dimensiune de 2 ori mai mare
        struct LinkedList *buckets_copy;
        // new_hmax va fi noua dimensiune a array-ului de liste
        int new_hmax = ht->hmax * 2;
        // initializez array-ul de buckets de 2 ori mai mare decat vechiul array
        buckets_copy  = malloc(new_hmax * sizeof(struct LinkedList));
        // parcurg buckets din Hashmap
        for (int index = 0; index < ht->hmax; index++) {

             // initalizez noua lista[index]
            init_list(&buckets_copy[index]);

            // ma pozitionez cu curr pe head-ul vechii liste[index] si o parcurg 
            // pentru a copia nod cu nod informatia si a o introduce in lista din noul array
            struct Node * curr = ht->buckets[index].head;
            
            // list e un pointer la lista[index] din noul array
            struct LinkedList *list = &buckets_copy[index];
            while (curr != NULL) {
                // adaug nod cu nod in noua lista
                add_nth_node(list, list->size, ((struct info *)curr->data));
                curr = curr->next;
            }
        }
        // eliberez vectorul de liste
        free(ht->buckets);
        ht->buckets = NULL;
        // mut pointer-ul din hashtable la noul array
        ht->buckets = buckets_copy;
        // redimensionez array-ul de liste la noua dimensiune
        ht->hmax = new_hmax;
    
    }
   
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
    informatii_movie[1].regizor = "Toby Whithouse";
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


    ht_movies = malloc(sizeof(struct Hashtable));
    init_ht(ht_movies, 10, hash_function_string, compare_function_strings);

    put(ht_movies, "Being Human", strlen("Being Human") + 1, &informatii_movie[0]);
    put(ht_movies, "Being human", strlen("Being human") + 1, &informatii_movie[1]);
    put(ht_movies, "Avatar", strlen("Avatar") + 1, &informatii_movie[2]);
    put(ht_movies, "The edge of seventeen", strlen("The edge of seventeen") + 1, &informatii_movie[3]);
    put(ht_movies, "Twilight", strlen("Twilight") + 1, &informatii_movie[4]);
    put(ht_movies, "Edge of Fear", strlen("Edge of Fear") + 1, &informatii_movie[5]);
    put(ht_movies, "Twilight", strlen("Twilight") + 1, &informatii_movie[6]);
    put(ht_movies, "Edge of Fear", strlen("Edge of Fear") + 1, &informatii_movie[7]);

    // functia de redimensioare
    resize(ht_movies);
    printf("Noua dimensiune e %d\n", ht_movies->hmax);
    //printez si eliberez hashtable-ul
    print_hash(ht_movies);
    free_ht(ht_movies);

    return 0;
 }