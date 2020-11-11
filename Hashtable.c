/*
 * Hashtable.c
 * Alexandru-Cosmin Mihai
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashtable.h"



/*
 * Functii de comparare a cheilor:
 */
int compare_function_ints(void *a, void *b) {
    int int_a = *((int *)a);
    int int_b = *((int *)b);

    if (int_a == int_b) {
        return 0;
    } else if (int_a < int_b) {
        return -1;
    } else {
        return 1;
    }
}

int compare_function_strings(void *a, void *b) {
    char *str_a = (char *)a;
    char *str_b = (char *)b;

    return strcmp(str_a, str_b);
}

/*
 * Functii de hashing:
 */
unsigned int hash_function_int(void *a) {
    /*
     * Credits: https://stackoverflow.com/a/12996028/7883884
     */
    unsigned int uint_a = *((unsigned int *)a);

    uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
    uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
    uint_a = (uint_a >> 16u) ^ uint_a;
    return uint_a;
}

unsigned int hash_function_string(void *a) {
    /*
     * Credits: http://www.cse.yorku.ca/~oz/hash.html
     */
    unsigned char *puchar_a = (unsigned char*) a;
    unsigned long hash = 5381;
    int c;

    while ((c = *puchar_a++))
        hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

    return hash;
}

/*
 * Functie apelata dupa alocarea unui hashtable pentru a-l initializa.
 * Trebuie alocate si initializate si listele inlantuite.
 */
void init_ht(struct Hashtable *ht, int hmax, unsigned int (*hash_function)(void*), int (*compare_function)(void*, void*)) {
    
    // aloc un vector de liste
    ht->buckets  = malloc(hmax * sizeof(struct LinkedList));
    int i;
    for (i = 0; i < hmax; i++) {
        // o initializez fiecare lista din vector
        init_list(&ht->buckets[i]);
    }
    ht->hash_function = hash_function;
    ht->compare_function = compare_function;
    ht->hmax = hmax;
    ht->size = 0;

}

/*
 * Atentie! Desi cheia este trimisa ca un void pointer (deoarece nu se impune tipul ei), in momentul in care
 * se creeaza o noua intrare in hashtable (in cazul in care cheia nu se gaseste deja in ht), trebuie creata o copie
 * a valorii la care pointeaza key si adresa acestei copii trebuie salvata in structura info asociata intrarii din ht.
 * Pentru a sti cati octeti trebuie alocati si copiati, folositi parametrul key_size_bytes.
 *
 * Motivatie:
 * Este nevoie sa copiem valoarea la care pointeaza key deoarece dupa un apel put(ht, key_actual, value_actual),
 * valoarea la care pointeaza key_actual poate fi alterata (de ex: *key_actual++). Daca am folosi direct adresa
 * pointerului key_actual, practic s-ar modifica din afara hashtable-ului cheia unei intrari din hashtable.
 * Nu ne dorim acest lucru, fiindca exista riscul sa ajungem in situatia in care nu mai stim la ce cheie este
 * inregistrata o anumita valoare.
 */
void put(struct Hashtable *ht, void *key, int key_size_bytes, void *value) {
    /* TODO */
    int index = ht->hash_function(key) % ht->hmax;
    // pointez pe primul element din lista corespunzatoare
    struct Node *curr = ht->buckets[index].head;
    while (curr != NULL && ht->compare_function(key,((struct info *)curr->data)->key) != 0)
        curr = curr->next;
    // daca nu l-am gasit trebuie adaugat
    if(curr == NULL)  {
        // aloc copia
        struct info *new = malloc(sizeof(struct info));
        new->key = malloc(key_size_bytes);
        // copiez cheia
        memcpy(new->key, key, key_size_bytes);
        // copiez valorea cheii
        new->value = value;
        //adaug nodul cu "valoarea"<=> "data", new, in lista buckets[index] la final
        add_nth_node(&ht->buckets[index],ht->buckets[index].size,new);
        ht->size++;
    }
    else    // actualizez value de la respectiva key   
        ((struct info *)(curr->data))->value = value;
    return;
    }

void* get(struct Hashtable *ht, void *key) {
    /* TODO */
    // calculez indexul listei pe baza key
    int index = ht->hash_function(key)%ht->hmax;
    // ma plasez cu curr la inceputul listei cu indexul specific
    struct Node * curr = ht->buckets[index].head;
    // verific fiecare element din lista
    for (int i = 0; i < ht->buckets[index].size; i++) {
        if (ht->compare_function(((struct info *)curr->data)->key,key) == 0) return (((struct info *)curr->data)->value);
        curr = curr->next;
    }
    return NULL;
}

/*
 * Functie care intoarce:
 * 1, daca pentru cheia key a fost asociata anterior o valoare in hashtable folosind functia put
 * 0, altfel.
 */
int has_key(struct Hashtable *ht, void *key) {
    /* TODO */
    // calculez indexul listei pe baza key
    int index = ht->hash_function(key)%ht->hmax;
    // ma plasez cu curr la inceputul listei cu indexul specific
    struct Node * curr = ht->buckets[index].head;
    // verific fiecare element din lista
    for (int i = 0; i < ht->buckets[index].size; i++) {
        if (ht->compare_function(((struct info *)curr->data)->key,key) == 0) return 1;
        curr = curr->next;
    }

    return 0;
}

/*
 * Procedura care elimina din hashtable intrarea asociata cheii key.
 * Atentie! Trebuie avuta grija la eliberarea intregii memorii folosite pentru o intrare din hashtable (adica memoria
 * pentru copia lui key --vezi observatia de la procedura put--, pentru structura info si pentru structura Node din
 * lista inlantuita).
 */
void remove_ht_entry(struct Hashtable *ht, void *key) {

    int i, poz;
    struct Node *curr;
    // calculez indexul pe baza key
    i = ht->hash_function(key) % ht->hmax;
    // ma pozitionez pe head-ul listei cu acel index
    curr = ht->buckets[i].head;
    poz = 0;
    // caut cheia in lista
    while(curr != NULL && ht->compare_function(((struct info*)curr->data)->key, key) != 0)
    {	
    	curr = curr->next;
    	poz++;
    }
    // daca nu o gasesc ies din functie
    if(curr == NULL)
    	return;
    // daca o gasesc eliberez memoria asociata acelui nod si continutului din el
    free(((struct info *)curr->data)->key);
    free(((struct info *)curr->data));
    // elimin nodul
    curr = remove_nth_node(&ht->buckets[i], poz);
    free(curr);
    // scade nr de noduri din array
    ht->size--;
}

/*
 * Procedura care elibereaza memoria folosita de toate intrarile din hashtable, dupa care elibereaza si memoria folosita
 * pentru a stoca structura hashtable.
 */
void free_ht(struct Hashtable *ht) {
    
    int i;
    // parcurg vectorul de buckets
    for (i = 0; i < ht->hmax; i++) {
        // eliberez fiecare lista. daca nu e goala
            while (ht->buckets[i].size > 0) {
                // sterg datele head-ului listei[i]
            free(((struct info*)ht->buckets[i].head->data)->key);
            free(((struct info*)ht->buckets[i].head->data));
            // sterg head-ul listei, cat timp are head
            struct Node * head_node = remove_nth_node(&(ht->buckets[i]), 0);
            free(head_node);
            ht->size--;
        }
        }
        // eliberez vectorul
    free(ht->buckets);
    // eliberez hashtable
    free(ht);
}

int get_ht_size(struct Hashtable *ht) {
    if (ht == NULL) {
        return -1;
    }

    return ht->size;
}

int get_ht_hmax(struct Hashtable *ht) {
    if (ht == NULL) {
        return -1;
    }

    return ht->hmax;
}
