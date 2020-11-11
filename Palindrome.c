#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Dequeue.c"
#include "LinkedList.c"

int main() {
    
    struct Dequeue *dq = malloc(sizeof(struct Dequeue));
    if (dq == NULL) {
        perror("Not enough memory to create the dequeue!");
        return -1;
    }

    char numar[40], fr_val, bk_val;
    int i, ok = 1;
    // citesc numarul
    scanf("%s",numar);
    // initializez coada
    init_dq(dq);
    for(i = 0; i < strlen(numar); i++) {

        // adaug fiecare cifra in dequeue, in ordine inversa
        add_first(dq, &numar[i]);
    }
    int size = get_size_dq(dq);
    // cat timp mai am cel putin o cifra in numar si au fost cifrele egale
    while(size >= 1 && ok == 1) {

            // extrag cifrele egal departate de mijloc, din numar
            fr_val = *(char *)front(dq);
            bk_val = *(char *)back(dq);
            // daca cifrele egal departate sunt diferite opresc algoritmul
            if(fr_val != bk_val) {
                ok = 0;
            }
            // altfel le scot din coada si tin cont de noua dimensiune a cozii
            else {
                remove_first(dq);
                remove_last(dq);
                size = get_size_dq(dq);
            }

    }

    // verific daca e sau nu palindrom
    if(ok == 1) printf("Este palindrom!\n");
    else printf("Nu este palindrom!\n");
    
    // eliberez memoria
    purge_dq(dq);
    free(dq);
    
    return 0;
}