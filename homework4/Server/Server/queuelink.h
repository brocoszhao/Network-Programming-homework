#pragma once
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

struct queue_node
{
	const char *a;
	struct queue_node *next;
};
typedef struct queue_node queue_list;
typedef queue_list *link;
link front = NULL;
link rear = NULL;

void addqueue(const char *string)
{
	link new_node;
	new_node = (link)malloc(sizeof(queue_list));

	new_node->a = string;
	new_node->next = NULL;
	if (rear == NULL)
		front = new_node;
	else
	{
		rear->next = new_node;
		rear = new_node;
	}
}

int dequeue()
{
	link top;
	const char *temp;
	if (front != NULL)
	{
		top = front;
		front = front->next;
		temp = top->a;
		free(top);
		return *temp;
	}
	else
		return -1;
}