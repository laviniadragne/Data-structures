#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "Queue.h"
#include "Stack.h"

#define MAX_NODES 100
#define INF  99999

// EXERCITIUL 1

// functie de vizitare a unui nod pentru dfs
void visit_node(int node, int *visited, LinkedList *component) {

    visited[node] = 2;
    add_nth_node(component, component->size, &node);

}

// EXERCITIUL 1

// functia dfs pentru componente conexe
void dfs_connected_comps(ListGraph *lg, int node, int *visited, LinkedList *component) {
    /* TODO */
     Stack *st = malloc(sizeof(Stack));
    if (st == NULL) {
        perror("Not enough memory to create the stack!");
        return ;
    }
    init_stack(st);
    // vizitez nodul sursa si il adaug in lista component si in stiva
    visit_node(node, visited, component);
    push_stack(st, &node);
    // cat timp stiva nu e goala
    while(st->list->size) {
        int top = *(int *)peek_stack(st);
        int i = 0;
        // aflu primul vecin nevizitat al lui top
        Node *curr = lg->neighbors[top]->head;
        int ok = 0;
        while(curr != NULL && ok == 0) {
            i = *(int *)(curr->data);
            // daca e alb, adica nu a fost vizitat
            if(visited[i] == 1 && i != node) ok = 1;
            else curr = curr->next;
        }
        // daca l-am gasit il adaug in stiva
        if(ok == 1) {
            visit_node(i, visited, component);
            push_stack(st, &i);
        }
        // altfel il scot din stiva si il fac negru
        else {

            visited[top] = 3;
            pop_stack(st);
        }

        }
        // golesc stiva
    purge_stack(st);
    free(st);
}

// EXERCITIUL 1

// functia de afisare a tuturor componentelor conexe
void connected_components(ListGraph *lg) {
    /* TODO */
    LinkedList *component;
    int visited[MAX_NODES];
    // fac toate nodurile albe
    for(int i = 0; i < lg->nodes; i++) {
        visited[i] = 1;
    }
    // initializez numarul de componente conexe cu 0
    int componente = 0;
    printf("Componetele conexe sunt:\n");
    for(int i = 0; i < lg->nodes;i ++) {

        // daca nodul e alb, inseamna ca din el porneste o noua
        // componenta conexa
        if(visited[i] == 1) {
            // aloc si initializez lista pentru componenta noua conexa
            component = malloc(sizeof(LinkedList));
            init_list(component);
            // pornesc dfs-ul din nodul i
            dfs_connected_comps(lg, i, visited, component);
            // cresc numarul de componente si afisez lista, in final
            componente++;
            print_int_linkedlist(component);
            free_list(&component);
        }

    }
    printf("Numarul de componente conexe este: %d\n",componente);
    
}

// EXERCITIUL 3

// functie de vizitare al unui nod pentru dfs-ul de la sortarea topologica 
int visit_node_dfs(int node, int *visited, int *t_desc, int contor_t, LinkedList *result) {

    t_desc[node] = contor_t;
    contor_t++;
    visited[node] = 2;
    add_nth_node(result, result->size, &node);
    return contor_t;
}

// EXERCITIUL 3

// functia de dfs pentru sortarea topologica
int dfs_topo_sort(ListGraph *lg, int node, int *visited, LinkedList *result, int *t_desc, int *t_fin, int time) {
    /* TODO */
    Stack *st = malloc(sizeof(Stack));
    if (st == NULL) {
        perror("Not enough memory to create the stack!");
        exit(-1) ;
    }

    init_stack(st);
    // vizitez nodul sursa
    time = visit_node_dfs(node, visited, t_desc, time, result);
    push_stack(st, &node);
    // cat timp stiva nu e goala
    while(st->list->size) {
        int top = *(int *) peek_stack(st);
        int i = 0;
        // aflu primul vecin nevizitat al lui top
        Node *curr = lg->neighbors[top]->head;
        int ok = 0;
        while(curr != NULL && ok == 0) {
            i = *(int *)(curr->data);
            // daca e alb, adica nu a fost vizitat, sau e negru
            if(visited[i] == 1 && i != node) ok = 1;
            else curr = curr->next;
        }
        // daca l-am gasit il adaug in stiva
        if(ok == 1) {
            time = visit_node_dfs(i, visited, t_desc, time, result);
            push_stack(st, &i);
        }
        // altfel il scot din stiva si il fac negru
        else {
            
            t_fin[top] = time;
            time ++;
            visited[top] = 3;
            pop_stack(st);
        }

        }
        // golesc stiva
    purge_stack(st);
    free(st);
    return time;
}

// EXERCITIUL 3

// functie prin care verific daca un graf are sau nu cicluri
// functia este utila pentru a face sortare topologica, pentru ca
// doar un graf aciclic poate fi sortat topologic
// daca graful este ciclic se afiseaza un mesaj corespunzator 

int circular(ListGraph *lg, int node, int *visited, LinkedList *result, int *t_desc, int *t_fin, int time) {

    // initializez numarul de cicluri
    int cicluri = 0;
    Stack *st = malloc(sizeof(Stack));
    if (st == NULL) {
        perror("Not enough memory to create the stack!");
        exit(-1);
    }

    init_stack(st);
    // vizitez nodul sursa
    time = visit_node_dfs(node, visited, t_desc, time, result);
    visited[node] = 1;
    push_stack(st, &node);
    // cat timp stiva nu e goala
    while(st->list->size) {
        int top = *(int *)peek_stack(st);
        int i = 0;
        // aflu primul vecin nevizitat al lui top
        Node *curr = lg->neighbors[top]->head;
        int ok = 0;
        while(curr != NULL && ok == 0) {
            i = *(int *)(curr->data);
            // daca e alb, adica nu a fost vizitat
            if(visited[i] == 1) {
                    // daca nu e nodul din care am plecat
                    if(i != node) 
                        ok = 1;
                    // am ajuns din nou la nodul din care am plecat
                    // deci am un ciclu
                    else {
                        cicluri = 1;
                        purge_stack(st);
                        free(st);
                        return cicluri;
                    }
                }
            else curr = curr->next;
        }
        // daca l-am gasit il adaug in stiva
        if(ok == 1) {
            time = visit_node_dfs(i, visited, t_desc, time, result);
            push_stack(st, &i);
        }
        // altfel il scot din stiva si il fac negru
        else {
            
            t_fin[top] = time;
            time ++;
            visited[top] = 3;
            pop_stack(st);
        }

        }
    // golesc stiva
    purge_stack(st);
    free(st);
    return cicluri;
}

// EXERCITIUL 3

// functia verifica mai intai daca un graf dat este ciclic si in caz contrar afiseaza
// o posibila sortare topologica
void topo_sort(ListGraph *lg, int *nodes_index) {
    /* TODO */
    int time = 0;
    LinkedList *result;
    int visited[MAX_NODES],t_desc[MAX_NODES], t_fin[MAX_NODES];
    // initializez nodurile
    for(int i = 0; i < lg->nodes; i++) {
        visited[i] = 1;
        t_desc[i] = 0;
        t_fin[i] = 0;
    }
    // verific daca are cicluri
    int cic = 0;
    int i = 0;
    while(i < lg->nodes && cic == 0) {

        if(visited[i] == 1) {
            result = malloc(sizeof(LinkedList));
            init_list(result);
            // verific daca are cicluri
            cic = circular(lg, i, visited, result, t_desc, t_fin, time);
            free_list(&result);
            }
            i++;

    }
    // daca este aciclic poate fi sortat topologic
    if(cic == 0) {

    // initializez nodurile
    for( i = 0; i < lg->nodes; i++) {
        visited[i] = 1;
        t_desc[i] = 0;
        t_fin[i] = 0;
    }

    time = 0;
    for( i = 0; i < lg->nodes; i++) {

        // daca nodul e alb
        if(visited[i] == 1) {
            result = malloc(sizeof(LinkedList));
            init_list(result);
            time = dfs_topo_sort(lg, i, visited, result, t_desc, t_fin, time);
            free_list(&result);
            }
            

    }
    // sortare descrescatoare dupa timpul de finalizare
    int aux;
    for( i = 0; i < lg->nodes - 1; i++) {
        for(int j = i + 1; j < lg->nodes; j++) {
            if(t_fin[i] < t_fin[j]) {
                aux = nodes_index[i];
                nodes_index[i] = nodes_index[j];
                nodes_index[j] = aux;
                aux = t_fin[i];
                t_fin[i] = t_fin[j];
                t_fin[j] = aux;

            }
        }
    }
    // afisez nodurile sortate
    printf("Sortarea topologica este:\n");
    for(int j = 0; j < lg->nodes; j++) {
            printf("%d ",nodes_index[j]);
        }
    }
    else printf("Graful are un ciclu, nu poate fi sortat topologic!\n");

}

// EXERCITIUL 2 

// functie de initializare a nodurilor pentru distanta minima dintre 2 puncte
void init_bfs(int n, int *visited, int *parents, int *distance) {

    for(int i = 0; i < n; i++) {
        visited[i] = 1;
        parents[i] = -1;
        distance[i] = INF;

    }
}

// EXERCITIUL 2 

// functie de bfs pentru a calcula distatnta minima dintre 2 puncte
void path_bfs(ListGraph *lg, int node, int *visited, int *parents, int *distance) {

    Queue *q = malloc(sizeof(Queue));
    if (q == NULL) {
        perror("Not enough memory to create the queue!");
        return ;
    }
    init_q(q);

    int i;
    // incep procesarea nodului sursa si il adaug in coada
    visited[node] = 2;
    distance[node] = 0;
    enqueue(q,&node);
    // cat timp coada nu e goala
    while(q->list->size != 0) {

        int v = *(int *)(q->list->head->data);
        // extrag nodul din coada
        dequeue(q);
        // pentru fiecare din vecinii lui v
        Node *curr = lg->neighbors[v]->head;
        while(curr != NULL) {
            i = *(int *)(curr->data);
            // daca e alb il fac gri, il printez si ii retin parintele si distanta fata de el
            if(visited[i] == 1) {
                visited[i] = 2;
                parents[i] = v;
                distance[i] = distance[v]+1;
                enqueue(q,&i);
            }
            curr = curr->next;
        }
        // schimb culoarea lui v in negru
        visited[v] = 3;
    }
    purge_q(q);
    free(q);
}

// EXERCITIUL 2 

// functia pentru drum minim intre 2 noduri
void min_path(ListGraph *lg, int sursa, int destinatie) {
    /* TODO */
    
        int visited[MAX_NODES], parents[MAX_NODES], distance[MAX_NODES], path[MAX_NODES], c = 0;
        // initializez nodurile
        init_bfs(lg->nodes, visited, parents, distance);
        // aplic bfs-ul pentru nodul sursa
        path_bfs(lg, sursa, visited, parents, distance);
        printf("Distanta nodului %d fata de %d este: ", sursa, destinatie);
        // daca nu exista drum de la sursa la destinatie inseamna ca distanta e infinit
        if(distance[destinatie] == INF) 
            printf("INF ");
        else {
            // printez distanta
            printf("%d ", distance[destinatie]);
            printf("\n");
            printf("Drumul de la %d la %d este: ", sursa, destinatie);
            path[c] = destinatie;
            // retin parintii in ordine inversa in vectorul path
            while(parents[destinatie] != -1) {
                c++;
                path[c] = parents[destinatie];
                destinatie = parents[destinatie];
            }
            // afisez parintii
            for(int i = c; i >= 0; i--) {
                printf("%d ",path[i]);
            }
        }
        printf("\n");
}

// EXERCITIUL 4

// functia de bfs pentru a determina un graf bipartit
int bfs_bipartite(ListGraph *lg, int node, int *nivel) {

    Queue *q = malloc(sizeof(Queue));
    if (q == NULL) {
        perror("Not enough memory to create the queue!");
        exit(-1);
    }
    init_q(q);

    int i;
    // incep procesarea nodului sursa si il adaug in coada
    nivel[node] = 0;
    enqueue(q,&node);
    // cat timp coada nu e goala
    while(q->list->size != 0) {

        int v = *(int *)(q->list->head->data);
        // extrag nodul din coada
        dequeue(q);
        // pentru fiecare din vecinii lui v
        Node *curr = lg->neighbors[v]->head;
        while(curr != NULL) {
            i = *(int *)(curr->data);
                // daca nivelul lui i este nedefinit
                // initializez nivelul cu paritate inversa
                // fata de nodul de pe nivelul anterior
                if(nivel[i] == -1) {
                    if (nivel[v] == 0) {
                        nivel[i] = 1;
                    }
                    else {
                        nivel[i] = 0;
                    }
                    enqueue(q,&i);
                }
                // daca 2 noduri consecutive au acelasi nivel
                // graful nu este bipartit
                else {
                    if(nivel[i] == nivel[v]) {
                        purge_q(q);
                        free(q);
                        return 0;
                    }
                }
            curr = curr->next;
        }
    }
    purge_q(q);
    free(q);
    // s-a terminat parcurgerea fara ca 2 noduri consecutive sa
    // aiba acelasi nivel, deci graful e bipartit
    return 1;
}

// EXERCITIUL 4

// functie de initializare pentru graful bipartit
void init_bipartite(int n, int *color) {
    for(int i = 0; i < n; i++) {
        color[i] = -1;
    }
}

// EXERCITIUL 4

// functie de verificare daca un graf este sau nu bipartit
int check_bipartite(ListGraph *lg, int *color) {
    /* TODO */
    int ok = 1;
    init_bipartite(lg->nodes, color);
    for(int j = 0; j < lg->nodes; j++) {

        // daca graful este nevizitat
        if(color[j] == -1) {
            ok = bfs_bipartite(lg, j, color);
            if(ok == 0) break;
        }
    }
    return ok;
}

int main() {
    int nodes, edges;
    int color[MAX_NODES];
    int nodes_index[MAX_NODES];
    int x[MAX_NODES], y[MAX_NODES];
    ListGraph *lg = malloc(sizeof(ListGraph));

    scanf("%d %d", &nodes, &edges);
    init_list_graph(lg, nodes);
    for (int i = 0; i < nodes; ++i) {
        nodes_index[i] = i;
    }

    for (int i = 0; i < edges; ++i) {
        scanf("%d %d", &x[i], &y[i]);
        add_edge_list_graph(lg, x[i], &y[i]);
    }

    /* Ex 1 */
    connected_components(lg);

    /* Ex 2 */
    topo_sort(lg, nodes_index);

    /* Ex 3 */

    printf("\nIntroduceti un nod sursa si unul destinatie");
    int sursa, destinatie;
    scanf("%d %d",&sursa, &destinatie);

    if((sursa < lg->nodes) && (destinatie < lg->nodes))
        min_path(lg, sursa, destinatie);
    else 
        printf("Nu exista aceste noduri in graf!\n");

    /* Ex 4 */
    if (check_bipartite(lg, color)) {
        printf("Grafurile bipartite:\n");
        for (int i = 0; i < lg->nodes; ++i) {
            if (color[i] == 1) {
                printf("%d ", i);
            }
        } 
        printf("\n");
        for (int i = 0; i < lg->nodes; ++i) {
            if (color[i] == 0) {
                printf("%d ", i);
            }
        } 
        printf("\n");
    } else {
        printf("The graph is not bipartite\n");
    }

    clear_list_graph(lg);
    free(lg);
    return 0;
}