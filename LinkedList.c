#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

/*
 * Functie care trebuie apelata dupa alocarea unei liste simplu inlantuite, pentru a o initializa.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
void init_list(struct LinkedList *list) {

    list->head = NULL; 
    list->size = 0;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e adaugat pe pozitia n a listei
 * reprezentata de pointerul list. Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla
 * pe pozitia n=0). Daca n >= nr_noduri, noul nod se adauga la finalul listei. Daca n < 0, eroare.
 */
void add_nth_node(struct LinkedList *list, int n, void *new_data) {

  struct Node * new;
    if (list==NULL || n < 0) {
         return ;
    }

  new = (struct Node*)malloc(sizeof(struct Node));

   struct Node *curr;
   new->data = new_data;
   new->next = NULL;
   
   // daca lista e goala
   if (list->size == 0) {
       list->head = new;
       list->head->next = NULL;
       list->size++;
       return ;
   }
   curr = list->head;
   // daca trebuie adaugat ca primul element
   if (n == 0) {
      new->next = list->head;
      list->head =new;
      list->size++;
      return ;
   }
   // daca il adaug la final
   if (n >= list->size) {
    n = list->size;
    while(curr->next)
    {
      curr = curr->next;
    }
    curr->next = new;
    new->next =NULL;
    list->size++;
    return ;
   }
   // daca il adaug aleator
   if (n < list->size) {
    int i;
    // curr va pointa pe nodul de pe pozitia i+1
    for (i = 0; i < n-1; i++)
    {
      curr = curr->next;
    }
    // new->next pointeaza pe nodul de pe pozitia n
    new->next = curr->next;
    curr->next = new;
    list->size++;
    return ;
   }
    
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca parametru.
 * Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din lista se afla pe pozitia n=0). Daca n >= nr_noduri - 1,
 * se elimina nodul de la finalul listei. Daca n < 0, eroare.
 * Functia intoarce un pointer spre acest nod proaspat eliminat din lista.
 * Este responsabilitatea apelantului sa elibereze memoria acestui nod.
 */
struct Node* remove_nth_node(struct LinkedList *list, int n) {

  if (list==NULL || list->head==NULL || n < 0) {
    exit (-1);
  }
  struct Node* first;
  // daca trebuie sa sterg primul nod
  if (n==0) {
    first = list->head;
    list->head = list->head->next;
    return first;
  }
    struct Node *last, *prev;
    // prev va pointa la anteriorul
    // last va pointa la urmatorul
    last = list->head->next;
    prev = list->head;
    // last = prev->next
    // daca il elimin pe ultimul
  if ( (n+1) >= list->size) {
    // cat timp n-am ajuns la ultimul
        while (last->next != NULL) {
          prev = last;
          last = last->next;
        }
      prev->next = NULL;
      list->size--;
      return last;
  }
  // 
  if ((n+1) < list->size) {
    int i;
    for (i = 0; i < n - 1; i++) {
       prev = last;
       last = last->next;
    }
    prev->next = last->next;
    list->size--;
    return last;
 }
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca parametru.
 */
int get_size(struct LinkedList *list) {

    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la sfarsit, elibereaza memoria folosita
 * de structura lista si actualizeaza la NULL valoarea pointerului la care pointeaza argumentul (argumentul este un
 * pointer la un pointer).
 */
void free_list(struct LinkedList **pp_list) {

    struct Node *curr, *new;
    new = (*pp_list)->head;
    while (new) {
      curr = new;
      new = new->next;
      free(curr);
    }
    free(*pp_list);
    * pp_list = NULL;
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza toate valorile int stocate in nodurile din lista inlantuita separate printr-un spatiu.
 */
void print_int_linkedlist(struct LinkedList *list) {

    struct Node *curr;
    if (list==NULL) {
    return ;
  }
    curr = list->head;
    while (curr != NULL) {
        printf("%d ", *((int *) curr->data));
        curr = curr->next;
    }
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza string-uri.
 * Functia afiseaza toate string-urile stocate in nodurile din lista inlantuita, separate printr-un spatiu.
 */
void print_string_linkedlist(struct LinkedList *list) {

    struct Node *curr;
    if (list==NULL) {
    return ;
  } 
    curr = list->head;
    if(curr->data==NULL) exit(-1);
    while (curr != NULL) {
        printf("%s ",(char *) (curr->data));
        curr = curr->next;
    }
    printf("\n");
}

int main() {
  
    struct LinkedList *list;
    struct Node *currNode;
    int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    list = malloc(sizeof(struct LinkedList));
    init_list(list);

    add_nth_node(list, 0, &numbers[10]);
    currNode = remove_nth_node(list, 0);
    printf("#1:\n");
    printf("Output: %d\n", *((int*)(currNode->data)));
    printf("Output asteptat: 10\n\n");
    free(currNode);

    add_nth_node(list, 0, &numbers[8]);
    currNode = remove_nth_node(list, 0);
    printf("#2:\n");
    printf("Output: %d\n", *((int*)(currNode->data)));
    printf("Output asteptat: 8\n\n");
    free(currNode);

    add_nth_node(list, 0, &numbers[0]);
    add_nth_node(list, 10, &numbers[1]);
    add_nth_node(list, 20, &numbers[2]);
    add_nth_node(list, 30, &numbers[3]);
    add_nth_node(list, 40, &numbers[4]);
    printf("#3:\n");
    printf("Output: ");
    print_int_linkedlist(list);
    printf("Output asteptat: 0 1 2 3 4\n\n");

    add_nth_node(list, 0, &numbers[0]);
    add_nth_node(list, 0, &numbers[1]);
    add_nth_node(list, 0, &numbers[2]);
    add_nth_node(list, 0, &numbers[3]);
    add_nth_node(list, 0, &numbers[4]);
    printf("#4:\n");
    printf("Output: ");
    print_int_linkedlist(list);
    printf("Output asteptat: 4 3 2 1 0 0 1 2 3 4\n\n");

    currNode = remove_nth_node(list, 0);
    free(currNode);
    printf("#5:\n");
    printf("Output: ");
    print_int_linkedlist(list);
    printf("Output asteptat: 3 2 1 0 0 1 2 3 4\n\n");

    currNode = remove_nth_node(list, 8);
    free(currNode);
    printf("#6:\n");
    printf("Output: ");
    print_int_linkedlist(list);
    printf("Output asteptat: 3 2 1 0 0 1 2 3\n\n");

    currNode = remove_nth_node(list, 0);
    free(currNode);
    currNode = remove_nth_node(list, 0);
    free(currNode);
    currNode = remove_nth_node(list, 0);
    printf("#7:\n");
    printf("Output: ");
    printf("%d\n", *((int*)currNode->data));
    free(currNode);
    printf("Output asteptat: 1\n\n");

    currNode = remove_nth_node(list, 40);
    free(currNode);
    currNode = remove_nth_node(list, 30);
    free(currNode);
    currNode = remove_nth_node(list, 20);
    free(currNode);
    currNode = remove_nth_node(list, 10);
    free(currNode);
    currNode = remove_nth_node(list, 0);
    free(currNode);
    add_nth_node(list, 0, &numbers[3]);
    add_nth_node(list, 1, &numbers[3]);
    add_nth_node(list, 2, &numbers[7]);
    add_nth_node(list, 0, &numbers[1]);
    printf("#8:\n");
    printf("Output: ");
    print_int_linkedlist(list);
    printf("Output asteptat: 1 3 3 7\n\n");

    currNode = remove_nth_node(list, 2);
    free(currNode);
    currNode = remove_nth_node(list, 1);
    free(currNode);
    printf("#9:\n");
    printf("Output: ");
    print_int_linkedlist(list);
    printf("Output asteptat: 1 7\n\n");

    free_list(&list);

    list = malloc(sizeof(struct LinkedList));
    init_list(list);

    add_nth_node(list, 0, "mere");
    add_nth_node(list, 0, "are");
    add_nth_node(list, 0, "Ana");
    printf("#10:\n");
    printf("Output: ");
    print_string_linkedlist(list);
    printf("Output asteptat: Ana are mere\n");

    free_list(&list);

    return 0;
}