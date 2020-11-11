#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Stack.h"
#include "LinkedList.h"
#include "Stack.c"
#include "LinkedList.c"

int main() {
    
    struct Stack *st = malloc(sizeof(struct Stack));
    if (st == NULL) {
        perror("Not enough memory to create the stack!");
        return -1;
    }

    char sir[40], crt_val;
    scanf("%s",sir);
    init_stack(st);
    int i, ok = 1;
    for(i = 0; i < strlen(sir); i++) {

        // citesc caracter cu caracter, daca e ({[ il adaug in stiva
        if(sir[i] == '(' || sir[i] == '{' || sir[i] == '[') push_stack(st, &sir[i]);
        else {
            // altfel e } sau ] sau )
                // stiva e goala si eu citesc } sau ) sau ]
                if(st->list->size == 0) 
                    { printf("Sir incorect parantezat!\n");
                        ok = 0;
                        // opresc for-ul
                        i = strlen(sir);
                    }
                    // stiva nu e goala
                else {
                    // vad care e elementul din varful stivei
                    crt_val = *(char *)peek_stack(st);
                    if (sir[i] == ')' && crt_val == '(') pop_stack(st);
                    else {
                        if (sir[i] == ']' && crt_val == '[') pop_stack(st);
                        else {
                            if (sir[i] == '}' && crt_val == '{') pop_stack(st);
                            else {
                                printf("Sir incorect parantezat!\n");
                                ok = 0;
                                // opresc for-ul
                                i = strlen(sir);
                                }
                            }
                        }
                    }
                }
    }
    
    // verific daca stiva a ramas goala si daca nu s-a oprit for-ul
    if(ok == 1) {
        int rest;
        rest = is_empty_stack(st);
        // stiva e goala
        if(rest == 1) printf("Sir parantezat corect!\n");
        // stiva mai are elemente
        else printf("Sir incorect parantezat!\n");
    }
    
    // eliberez memoria
    purge_stack(st);
    free(st);
    
    return 0;
}