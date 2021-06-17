#include <stdio.h>

#ifndef LIST_H_
#define LIST_H_

// ������� ���������� �������� � �������
// ������ ��� ������� ������
struct list1 {
	char sign, choose;
	int size;
	float *x, *y;
	struct list1 *next;
};



// ������ ��� �������� ������
struct list2 {
	float *res;
	struct list2 *res_next;
};



struct list1 *head, *current; //��������� �� ������ ������ � ������� �������

struct list2 *head_res, *current_res;

float* numb_list(char sign, float *x, float *y);

float* add_numb(FILE *input, int size);

void add_el(struct list1 *current, FILE *input);

void res_add_el(struct list2 *res_current, struct list1 *current);

#endif /* LIST_H_ */

