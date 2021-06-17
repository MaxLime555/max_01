#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

//ну повторяться не вижу смысла :)

void push_element(stack **head, float data) {
	stack *z = malloc(sizeof(stack));
	z->next = *head;
	z->data = data;
	*head = z;
}



float pop_element(stack **head) {
	stack *z;
	float data;
	z = *head;
	*head = (*head)->next;
	data = z->data;
	return data;
}
