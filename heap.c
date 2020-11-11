/**
 * SD, 2020
 * 
 * Lab #9, BST & Heap
 * 
 * Task #2 - Heap implementation
 */

#include "heap.h"
#include "utils.h"

heap_t *heap_create(int (*cmp_f) (const team_t *, const team_t *))
{
	heap_t *heap;

	heap = malloc(sizeof(heap_t));
	DIE(heap == NULL, "heap malloc");

	heap->cmp       = cmp_f;
	heap->size      = 0;
	heap->capacity  = 2;
	heap->arr       = malloc(heap->capacity * sizeof(team_t *));
	DIE(heap->arr == NULL, "heap->arr malloc");

	return heap;
}

static void __heap_insert_fix(heap_t *heap, int pos)
{
	team_t *tmp_team;
	int p = GO_UP(pos);
	/* TODO */
    while (pos > 0 && (heap->arr[p]->score < heap->arr[pos]->score)) {

    	// interschimb arr[p] cu arr[pos]
        tmp_team = heap->arr[p];
        heap->arr[p] = heap->arr[pos];
        heap->arr[pos] = tmp_team;

        pos = p;	// mut pos pe parinte
        p = GO_UP(pos); // noul parinte
   }

}

void heap_insert(heap_t *heap, team_t *team)
{
	char *rc;

	heap->arr[heap->size] = malloc(sizeof(team_t));
	DIE(heap->arr[heap->size] == NULL, "heap_insert malloc");

	heap->arr[heap->size]->name = calloc(TEAM_NAME_LEN, sizeof(char));
	DIE(heap->arr[heap->size]->name == NULL, "heap_insert name calloc");
	rc = strncpy(heap->arr[heap->size]->name, team->name, TEAM_NAME_LEN - 1);
	DIE(rc != heap->arr[heap->size]->name, "heap_insert name strncpy");
	heap->arr[heap->size]->score = team->score;

	__heap_insert_fix(heap, heap->size);

	heap->size++;
	if (heap->size == heap->capacity) {
		heap->capacity *= 2;

		heap->arr = realloc(heap->arr, heap->capacity * sizeof(team_t *));
		DIE(heap->arr == NULL, "heap->arr realloc");
	}
}

// peek
team_t heap_top(heap_t *heap)
{
	/* TODO */
	return *heap->arr[0];
}

// pushDown
static void __heap_pop_fix(heap_t *heap, int pos)
{
	team_t *tmp_team;
	int p = pos;
	int l = GO_LEFT(pos);
	int r = GO_RIGHT(pos);

	/* TODO */
	// am iesit din arbore
	if(l >= heap->size || r >= heap->size) return;
	// daca nu se respecta ordinea de parinte > descendenti
	int c1 = heap->cmp(heap->arr[p], heap->arr[l]);
	int c2 = heap->cmp(heap->arr[p], heap->arr[r]);
	int c3 = heap->cmp(heap->arr[l], heap->arr[r]);
	if(c1 < 0 || c2 < 0){
		// interschimb parintele cu cel mai mare dintre fii
		// fiul drept e mai mare
		if(c3 < 0) {
			tmp_team = heap->arr[p];
			heap->arr[p] = heap->arr[r];
			heap->arr[r] = tmp_team;
			// ma mut pe noul nod
			pos = r;
		}
		// fiul stang e mai mic
		else {
			tmp_team = heap->arr[p];
			heap->arr[p] = heap->arr[l];
			heap->arr[l] = tmp_team;
			// ma mut pe noul nod
			pos = l;
		}
		__heap_pop_fix(heap, pos);
	}
	else 
		return;


}

//remove from the first position
void heap_pop(heap_t *heap)
{
	free(heap->arr[0]->name);
	free(heap->arr[0]);

	heap->arr[0] = heap->arr[heap->size - 1];

	heap->size--;

	__heap_pop_fix(heap, 0);
}

int heap_empty(heap_t *heap)
{
	return heap->size <= 0;
}

void heap_free(heap_t *heap)
{
	/* TODO */
	for(int i = 0; i < heap->size; i++) {
		free(heap->arr[i]->name);
		free(heap->arr[i]);
	}
	free(heap->arr);
	free(heap);
}
