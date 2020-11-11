#include <stdlib.h>
#include <stdio.h>

#include "ListGraph.h"

void init_list_graph(ListGraph *graph, int nodes) {
    /* TODO */
    if(graph == NULL) return;
    graph->nodes = nodes;
    graph->neighbors = malloc(nodes * sizeof(LinkedList *));
    for (int i = 0; i < nodes; i++)
    {
    	graph->neighbors[i] = malloc(sizeof(LinkedList));
    	init_list(graph->neighbors[i]);
    }
}

void add_edge_list_graph(ListGraph *graph, int src, int *dest) {
    /* TODO */
    if(graph == NULL || graph->neighbors == NULL) return;
    if(graph->nodes <= src || graph->nodes <= *(int*) dest) return;
    struct Node * curr = graph->neighbors[src]->head;
    int ok = 0;

    // daca exista deja acea latura, nu o mai adaug
    while(curr != NULL && ok == 0) {
    	if(*(int *) curr->data == *(int *) dest) ok = 1;
    	curr = curr->next;
    }

    if(ok == 0) {
    	add_nth_node(graph->neighbors[src],graph->neighbors[src]->size,dest);
	}

}

int has_edge_list_graph(ListGraph *graph, int src, int dest) {
    /* TODO */
    if(graph == NULL || graph->neighbors == NULL || graph->neighbors[src]->head == NULL) return 0;
    if(graph->nodes <= src || graph->nodes <= dest) return 0;
    struct Node *curr = graph->neighbors[src]->head;
    while(*(int *)(curr->data) != dest && curr->next !=NULL) {
    	curr = curr->next;
    }
    if(*(int *)curr->data == dest) return 1;
    else return 0;

}

LinkedList* get_neighbours_list_graph(ListGraph *graph, int node) {
    /* TODO */
    if(graph == NULL || graph->neighbors == NULL || graph->neighbors[node] == NULL) return NULL;
    if(graph->nodes <= node) return NULL;
    return (graph->neighbors[node]);
}

void remove_edge_list_graph(ListGraph *graph, int src, int dest) {

    if(graph == NULL || graph->neighbors == NULL || graph->neighbors[src]->head == NULL) return;
    if(graph->nodes <= src || graph->nodes <= dest) return;
    struct Node *curr = graph->neighbors[src]->head;
    int poz = 0;
    while(*(int *)(curr->data) != dest && curr->next !=NULL) {
    	curr = curr->next;
    	poz++;
    }
    if(*(int *)curr->data == dest) {

    	struct Node * curr = remove_nth_node(graph->neighbors[src],poz);
    	free(curr);
    }
}

void clear_list_graph(ListGraph *graph) {
    /* TODO */
    if(graph == NULL) return;
    int i;
    // parcurg vectorul de liste
    for (i = 0; i < graph->nodes; i++) {
        // eliberez fiecare lista daca nu e goala
        free_list(&graph->neighbors[i]);
    }
        // eliberez vectorul
    free(graph->neighbors);

}