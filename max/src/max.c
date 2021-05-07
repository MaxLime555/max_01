/*Работа Клименко Максима(3 раз исправляю). Файловый калькулятор со списками
 * исправил передачу части параметров
 * при проверке ошибок никаких не выдал, инструкцию для работы напишу чуть ниже
 * Формат ввода: знак, s или v, количество координат векторов, данные.
 * пример входных данных для работы с числами: + s 4.6 -5
 * пример входных данных для работы с векторами: - v 5 4 -1 0,4 8 112 6
 * Надеюсь и верю, что третья попытка будет успешной :)
 */
#include <stdio.h>
#include <stdlib.h>

// список для входных данных
struct list1 {
	char sign, choose;
	int size;
	float *x, *y;
	struct list1 *next;
};

// список для выходных данных
struct list2 {
	float *res;
	struct list2 *res_next;
};
float* numb(char sign, float *x, float *y);
float* vect(char sign, int size, float *a, float *b);
float* add_numb(FILE *input, int size);
void add_el(struct list1 *current, FILE *input);
void res_add_el(struct list2 *res_current, struct list1 *current);
int main() {
	char n = 'y';
	char in[20], out[20];
	FILE *input, *output;
	struct list1 *head, *current; //указатели на начало списка и текущий элемент
	struct list2 *head_res, *current_res;
	while (n == 'y') {
		printf("\nInput file name: ");
		scanf("%s", in);
		printf("Output file name: ");
		scanf("%s", out);
		input = fopen(in, "r");
		if (feof(input) == 0) {
			head = malloc(sizeof(struct list1)); // память для первого элемента списка
			fscanf(input, " %c", &head->sign);
			fscanf(input, " %c", &head->choose);
			if (head->choose == 'v') {
				fscanf(input, " %i", &head->size);
			} else {
				head->size = 1;
			}
			if (head->sign != '!') {
				head->x = add_numb(input, head->size);
				head->y = add_numb(input, head->size);
			} else {
				head->x = add_numb(input, head->size);
				head->y = NULL;
			}
			current = head;

			while (feof(input) == 0) { // добавление элементов списка, пока не закончится файл
				add_el(current, input);
				current = current->next;

			}
			head_res = malloc(sizeof(struct list2)); // память для первого элемента списка для вывода
			current = head;
			if (current->choose == 'v') {
				head_res->res = vect(current->sign, current->size, current->x,
						current->y);
			} else {
				head_res->res = numb(current->sign, current->x, current->y);
			}
			head_res->res_next = NULL;
			current = current->next;
			current_res = head_res;
			while (current != NULL) { // пока элемент списка не последниий
				res_add_el(current_res, current);
				// переустановка указателей на следующий элемент
				current = current->next;
				current_res = current_res->res_next;
			}
			current = head;
			current_res = head_res;
			fclose(input);
			output = fopen(out, "w");
			while (current != NULL) //запись ответа в output
			{
				if (current->choose == 'v') {
					fprintf(output, "(");
					for (int i = 0; i < current->size; i++) {
						fprintf(output, " %.2f", current->x[i]);
					}
					fprintf(output, ") %c (", current->sign);
					for (int i = 0; i < current->size; i++) {
						fprintf(output, " %.2f", current->y[i]);
					}
					fprintf(output, " ) = ");
					if (current->sign != '*') {
						fprintf(output, "( ");
						for (int i = 0; i < current->size; i++) {
							fprintf(output, "%.2f ", current_res->res[i]);
						}
						fprintf(output, ")\n");
					} else {
						fprintf(output, "%.2f\n", current_res->res[0]);
					}
				} else if (current->choose == 's') {
					fprintf(output, " %.2f %c %.2f = %.2f\n", current->x[0],
							current->y[0], current->sign, current_res->res[0]);
				}
				current = current->next;
				current_res = current_res->res_next;
			}
			fclose(output);
		}
		printf("do you want to continue? (y/n)");
		scanf("%s", &n);
	}
	return 0;
}

// функция для операций с числами
float* numb(char sign, float *x, float *y) {
	float f, S, *res_numb;
	res_numb = malloc(sizeof(float));
	switch (sign) {
	case '+':
		res_numb[0] = x[0] + y[0];
		return res_numb;
	case '-':
		res_numb[0] = x[0] - y[0];
		return res_numb;
	case '*':
		res_numb[0] = x[0] * y[0];
		return res_numb;
	case '/':
		if (y != 0) {
			res_numb[0] = x[0] / y[0];
			return res_numb;
		} else {
			return 0;
		}
	case '!':
		f = 1;
		for (int i = 1; i <= x[0]; i++) {
			f *= i;
		}
		res_numb[0] = f;
		return res_numb;
	case '^':
		f = 1;
		S = 1;
		for (int i = 1; i <= y[0]; i++) {
			S *= x[0];
		}
		res_numb[0] = S;
		return res_numb;
	}
	return x;
	return y;
	free(x);
	free(y);
	free(res_numb);
}

// функция для операций с векторами
float* vect(char sign, int size, float *a, float *b) {
	float *res_vect;
	switch (sign) {
	case '+':
		res_vect = malloc(size * sizeof(float));
		for (int i = 0; i < size; i++) {
			res_vect[i] = a[i] + b[i];
		}
		return res_vect;
	case '-':
		res_vect = malloc(size * sizeof(float));
		for (int i = 0; i < size; i++) {
			res_vect[i] = a[i] - b[i];
		}
		return res_vect;
	case '*':
		res_vect = malloc(sizeof(float));
		res_vect[0] = 0;
		for (int i = 0; i < size; i++) {
			res_vect[0] += a[i] * b[i];
		}
		return res_vect;
	}
	return a;
	return b;
	free(a);
	free(b);
	free(res_vect);
}

// считывание указателей, добавление чисел
float* add_numb(FILE *input, int size) {
	float *numb;
	numb = malloc(size * sizeof(float));
	for (int i = 0; i < size; i++) {
		fscanf(input, "%f", &numb[i]);
	}
	return numb;
}

// добавление элемента списка для входных данных
void add_el(struct list1 *current, FILE *input) {
	struct list1 *z = malloc(sizeof(struct list1));
	fscanf(input, " %c", &z->sign);
	fscanf(input, " %c", &z->choose);
	if (z->choose == 'v') {
		fscanf(input, " %i", &z->size);
	} else {
		z->size = 1;
	}
	if (z->sign != '!') {
		z->x = add_numb(input, z->size);
		z->y = add_numb(input, z->size);
	} else {
		z->x = add_numb(input, z->size);
		z->y = NULL;
	}
	z->next = NULL; // последний элемент списка
	current->next = z; // переустановка указателя
}

// добавление элемента списка для выходных данных
void res_add_el(struct list2 *res_current, struct list1 *current) {
	struct list2 *z_res = malloc(sizeof(struct list1));
	if (current->choose == 'v') {
		z_res->res = vect(current->sign, current->size, current->x, current->y);
	} else {
		z_res->res = numb(current->sign, current->x, current->y);
	}
	z_res->res_next = NULL;
	res_current->res_next = z_res;
}
