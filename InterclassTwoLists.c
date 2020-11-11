#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int data;
	struct Node *next;
};

struct LinkedList
{
	struct Node	*head;
	int size;
};

struct LinkedList* create (int n,int *v)
{
	struct LinkedList *list;
	struct Node *new,*curr;
	int i;
	list = malloc(sizeof(struct LinkedList));
	list->head = NULL;
	new=malloc(sizeof(struct Node));
	new->data = v[0];	
	new->next = NULL;
	list->head = new;
	list->size=1;
	curr = new;
	for(i=1;i<n;i++)
	{
		new = malloc(sizeof(struct Node));
		new->data = v[i];
		new->next = NULL;
		curr->next = new;
		curr = new;
		(list->size)++;
	}
	return list;
}

void print(struct LinkedList *list)
{
	if(list == NULL)
		return;
	struct Node* curr;
	curr = list->head;
	while(curr != NULL)
	{
		printf("%d ",curr->data);
		curr = curr->next;
	}
	printf("\n");
}

struct LinkedList* inter(struct LinkedList *list1,struct LinkedList *list2)
{
	struct LinkedList *list;
	struct Node *curr1,*curr2,*new,*curr;
	list = malloc(sizeof(struct LinkedList));
	list->head = NULL;
	list->size = 0;
	new = malloc(sizeof(struct Node));
	new->next = NULL;
	list->head = new;
	list->size++;
	if(list1->head->data <= list2->head->data)
	{
		list->head->data = list1->head->data;
		curr1 = list1->head->next;
		curr2 = list2->head;
	}
	else
	{
		list->head->data = list1->head->data;		
		curr1 = list1->head;
		curr2 = list2->head->next;	
	}
	list->size++;
	list->head->next = NULL;
	curr = list->head;
	
	while(curr1->next && curr2->next)
	{
		new = malloc(sizeof(struct Node));
		new->next = NULL;
		curr->next = new;
		curr = new;
		if(curr1->data <= curr2->data)
		{
			new->data = curr1->data;
			curr1 = curr1->next;
		}
		else
		{
			new->data = curr2->data;		
			curr2 = curr2->next;
		}
	}

	while(curr1!= NULL)
	{
		new = malloc(sizeof(struct Node));
		new->next = NULL;
		curr->next = new;
		curr = new;
		new->data = curr1->data;
		curr1 = curr1->next;
	}

	while(curr2!= NULL)
	{
		new = malloc(sizeof(struct Node));
		new->next = NULL;
		curr->next = new;
		curr = new;
		new->data = curr2->data;
		curr2 = curr2->next;
	}
	return list;
}
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
int main()
{
	struct LinkedList *list1,*list2,*list;
	int v1[]={1,2,5,9};
	int v2[]={2,3,7,8,10};
	list1 = create(4,v1);
	print(list1);
	list2 = create(5,v2);
	print(list2);
	list = inter(list1,list2);
	print(list);
	free_list(&list1);
	free_list(&list2);
	free_list(&list);
	return 0;
}
