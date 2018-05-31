#pragma once
#include<stdlib.h>
#include<stdio.h>
#define Maxsize 100
int queue[Maxsize];
int front = -1;
int rear = -1;

void addqueue(const char *string)
{
	if (rear >= Maxsize)
		printf("The queue is full!");
	else
		rear++;
	queue[rear] = *string;
}

int dequeue()
{
	char *temp;

	if (front == rear)
		return -1;
	else
	{
		front++;
		*temp = queue[front];
		queue[front] = 0;
		return *temp;
	}
}

int main()
{
	addqueue("1234");
	addqueue("123456");
	for (int i = 0; i < Maxsize; i++)
	{
		if (queue[i] != NULL)
			printf("%s", queue[i]);
	}

	system("pause");
}
