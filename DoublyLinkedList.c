#include <stdio.h>
#include <stdlib.h>

#include "DoublyLinkedList.h"

/*
 * Functie care trebuie apelata dupa alocarea unei liste, pentru a o initializa.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
void init_list(struct DoublyLinkedList *list) {

    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe pozitia n=0).
 * Daca n >= nr_noduri, atunci se intoarce nodul de pe pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe
 * lista si am trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem afla pozitia dorita fara sa
 * simulam intreaga parcurgere?
 * Daca n < 0, eroare.
 */
struct Node* get_nth_node(struct DoublyLinkedList *list, int n) {

    // daca lista e goala sau nu exista lista sau pozitia nodului nu exista
    if (n < 0 || list->head == NULL || list ==NULL) return NULL;
    struct Node *curr = list->head;
    int i;
    // daca nodul depaseste lista
    if(n >= list->size) {
        n = n % list->size;
    }
    // daca nodul e in interiorul listei
    if(n < list->size) {
        for (i = 0; i < n; i++) {
            curr = curr->next;
        }
        return curr;
    }
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e adaugat pe pozitia n a listei
 * reprezentata de pointerul list. Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla
 * pe pozitia n=0).
 * Cand indexam pozitiile nu "ciclam" pe lista circulara ca la get, ci consideram nodurile in ordinea de la head la
 * ultimul (adica acel nod care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci adaugam nodul
 * nou la finalul listei. Daca n < 0, eroare.
 */
void add_nth_node(struct DoublyLinkedList *list, int n, void *new_data) {

    struct Node * new;
    if (list == NULL || n < 0) {
         return ;
    }

   new = (struct Node*)malloc(sizeof(struct Node));

   struct Node *first, *last;
   new->data = new_data;
   new->next = NULL;
   new->prev = NULL;
   
   // daca lista e goala
   if (list->size == 0) {
        list->head = new;
        list->tail = new;
        list->head->next = NULL;
        list->head->prev = NULL;
        list->size++;
        return ;
   }
   first = list->head;
   last = list->tail;
   // daca trebuie adaugat ca primul element
   if (n == 0) {
        // legatura primul-al doilea
        new->next = first;
        // legatura al doilea-primul
        first->prev = new;
        // legatura primul-NULL
        new->prev = NULL;
        list->head = new;
        list->size++;
        return ;
   }
   // daca il adaug la final
   if (n >= list->size) {
        n = list->size;
        // ultimul-primul si primul-ultimul
        last->next = new;
        new->prev = last;
        // ultimul-NULL
        new->next = NULL;
        list->tail = new;
        list->size++;
        return ;
   }
   // daca il adaug aleator
   if (n < list->size) {
        int i;
        // first pointeaza pe pozitia i+1
        for (i = 0; i < n-1; i++) {
            first = first->next;
        }
        // first va pointa pe pozitia n-1
        // legatura new - nodul de pe pozitia n
        new->next = first->next;
        first->next->prev = new;
        // legatura new - first (nodul de pe pozitia n - 1)
        first->next = new;
        new->prev = first;
        list->size++;
        return ;
   }

}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca parametru.
 * Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din lista se afla pe pozitia n=0).
 * Functia intoarce un pointer spre acest nod proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de
 * la finalul listei. Daca n < 0, eroare.
 * Este responsabilitatea apelantului sa elibereze memoria acestui nod.
 */
struct Node* remove_nth_node(struct DoublyLinkedList *list, int n) {
    
  if (list == NULL || list->head == NULL || n < 0) {
    return NULL;
  }
  struct Node* first = list->head;
  struct Node* last = list->tail;
  // daca trebuie sa sterg primul nod 
  if (n==0) {
    // mut inceputul listei pe a 2-a pozitie
    list->head = list->head->next;
    // fac legatura primul-NULL daca lista nu e goala deja(nu avea deja un element pe care l-am sters)
    if (list->head != NULL) list->head->prev = NULL;
    // daca lista e goala eliberez coada listei
    else list->tail = NULL;
    list->size--;
    return first;
  }
    struct Node *curr;
  if ( (n+1) >= list->size) {
    // legatura dintre penultimul si NULL
      last->prev->next = NULL;
      list->tail = last->prev;
      list->size--;
      return last;
  }
  // curr == first->next
  curr = list->head->next;
  // sterg aleator din lista
  if ((n+1) < list->size) {
    int i;
    for (i = 0; i < n - 1; i++) {
       first = curr;
       curr = curr->next;
    }
    // sar un nod
    first->next = curr->next;
    // refac si legatura inapoi
    curr->next->prev = first;
    list->size--;
    return curr;
 }

    return NULL;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca parametru.
 */
int get_size(struct DoublyLinkedList *list) {

    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la sfarsit, elibereaza memoria folosita
 * de structura lista.
 */
void free_list(struct DoublyLinkedList **pp_list) {

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
 * Functia afiseaza toate valorile int stocate in nodurile din lista separate printr-un spatiu, incepand de la primul
 * nod din lista.
 */
void print_int_list(struct DoublyLinkedList *list) {

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
 * Functia afiseaza toate string-urile stocate in nodurile din lista separate printr-un spatiu, incepand de la primul
 * nod din lista.
 */
void print_string_list(struct DoublyLinkedList *list) {

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

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza o singura data toate valorile int stocate in nodurile din lista, separate printr-un spatiu, incepand
 * de la nodul dat ca parametru si continuand la stanga in lista dublu inlantuita circulara, pana cand sunt afisate
 * valorile tuturor nodurilor.
 */
void print_ints_left_circular(struct Node *start) {

    struct Node* curr = start;
    if (start != NULL) {
    do {
        printf("%d ",*((int *) curr->data));
        curr = curr->prev;
    } while (curr!= NULL);
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza o singura data toate valorile int stocate in nodurile din lista, separate printr-un spatiu, incepand
 * de la nodul dat ca parametru si continuand la dreapta in lista dublu inlantuita circulara, pana cand sunt afisate
 * valorile tuturor nodurilor.
 */
void print_ints_right_circular(struct Node *start) {

    struct Node *curr = start;
    // daca exista acel nod de pornire
    if (start !=NULL) {
    do {
        printf("%d ",*((int *) curr->data));
        curr = curr->next;
    } while (curr!= NULL);
    }

    printf("\n");

}


int main() {
    struct DoublyLinkedList *list;
    struct Node *currNode;
    int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    list = malloc(sizeof(struct DoublyLinkedList));
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
    add_nth_node(list, 1, &numbers[1]);
    add_nth_node(list, 2, &numbers[2]);
    add_nth_node(list, 3, &numbers[3]);
    add_nth_node(list, 4, &numbers[4]);
    printf("#3:\n");
    printf("Output: ");
    print_int_list(list);
    printf("Output asteptat: 0 1 2 3 4\n\n");

    add_nth_node(list, 0, &numbers[0]);
    add_nth_node(list, 0, &numbers[1]);
    add_nth_node(list, 0, &numbers[2]);
    add_nth_node(list, 0, &numbers[3]);
    add_nth_node(list, 0, &numbers[4]);
    printf("#4:\n");
    printf("Output: ");
    print_int_list(list);
    printf("Output asteptat: 4 3 2 1 0 0 1 2 3 4\n\n");

    currNode = remove_nth_node(list, 0);
    free(currNode);
    printf("#5:\n");
    printf("Output: ");
    print_int_list(list);
    printf("Output asteptat: 3 2 1 0 0 1 2 3 4\n\n");

    currNode = remove_nth_node(list, 8);
    free(currNode);
    printf("#6:\n");
    printf("Output: ");
    print_int_list(list);
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

    currNode = remove_nth_node(list, 4);
    free(currNode);
    currNode = remove_nth_node(list, 3);
    free(currNode);
    currNode = remove_nth_node(list, 2);
    free(currNode);
    currNode = remove_nth_node(list, 1);
    free(currNode);
    currNode = remove_nth_node(list, 0);
    free(currNode);
    add_nth_node(list, 0, &numbers[3]);
    add_nth_node(list, 1, &numbers[3]);
    add_nth_node(list, 2, &numbers[7]);
    add_nth_node(list, 0, &numbers[1]);
    printf("#8:\n");
    printf("Output: ");
    print_int_list(list);
    printf("Output asteptat: 1 3 3 7\n\n");

    currNode = remove_nth_node(list, 2);
    free(currNode);
    currNode = remove_nth_node(list, 1);
    free(currNode);
    printf("#9:\n");
    printf("Output: ");
    print_int_list(list);
    printf("Output asteptat: 1 7\n\n");

    add_nth_node(list, 2, &numbers[8]);
    add_nth_node(list, 1, &numbers[2]);
    add_nth_node(list, 0, &numbers[0]);
    add_nth_node(list, 5, &numbers[9]);
    add_nth_node(list, 3, &numbers[3]);
    printf("#10:\n");
    printf("Output: ");
    print_int_list(list);
    printf("Output asteptat: 0 1 2 3 7 8 9\n\n");

    currNode = get_nth_node(list, 4);
    printf("#11:\n");
    printf("Output: ");
    print_ints_left_circular(currNode);
    printf("Output asteptat: 7 3 2 1 0 9 8\n\n");

    currNode = get_nth_node(list, 2);
    printf("#12:\n");
    printf("Output: ");
    print_ints_right_circular(currNode);
    printf("Output asteptat: 2 3 7 8 9 0 1\n\n");

    free_list(&list);

    list = malloc(sizeof(struct DoublyLinkedList));
    init_list(list);

    add_nth_node(list, 0, "mere");
    add_nth_node(list, 0, "are");
    add_nth_node(list, 0, "Ana");
    printf("#13:\n");
    printf("Output: ");
    print_string_list(list);
    printf("Output asteptat: Ana are mere\n");

    free_list(&list);

    return 0;
}