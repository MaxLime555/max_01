// Пример работы с калькулятором:
// Вводим s или v в зависимости от того, какой калькулятор хотим использовать
//Затем количество координат векторов(если векторный)
//Данные
//Пример для работы с числами + s 2.3 -2
//Причер для работы с векторами - v 3 5 -2 0,1 9 105 0
//Ну и после завершения работы перезапустить программу(если понадобится)
#include <stdio.h>
#include <stdlib.h>
// Работа Клименко Максима. Использование списков для хранения массива данных с произвольным количеством элементов.
// Весь калькулятор пришлось переиначить, кроме названий переменных почти ничего от старого не осталось :(
// Но прикольно, пошевелить мозгами и убить часиков 5 полезно.
// Надеюсь, что я нигде не накосячил и переменные правильно поставил.
// Список для входных данных.
struct list1 {
	char n, z;
	int size;
	float *a, *b;
	struct list1 *next;
};

// Список тут для выходных данных.
struct list2 {
	float *h;
	struct list2 *res_next;
};

float* numb(char z, float *a, float *b);
float* vect(char z, int h, float *x, float *y);
float* add_numb(FILE *input, int size);
void add_el(struct list1 *current, FILE *input);
void res_add_el(struct list2 *res_current, struct list1 *current);

int main(int argc, char *argv[]) {
	char e;
	char in[20], out[20];

    FILE *input, *output;
    struct list1 *head, *current;    // указатели на начало списка и текущий элемент
    struct list2 *head_res, *current_res;

	while (e == 'y') {
		printf("\nВведите имя вводного файла: ");
		scanf("%s", in);
		printf("Введите имя выводного файла: ");
		scanf("%s", out);
		input = fopen(in, "r");
		if (feof(input) == 0) {
			head = malloc(sizeof(struct list1));    // память для первого элемента списка
			fscanf(input, " %c", &head->z);
			fscanf(input, " %c", &head->n);
			if (head->n == 'v') {
				fscanf(input, " %i", &head->size);
			} else {
				head->size = 1;
			}
			if (head->z != '!') {
				head->a = add_numb(input, head->size);
				head->b = add_numb(input, head->size);
			} else {
				head->a = add_numb(input, head->size);
				head->b = NULL;
			}
			current = head;
				while (feof(input) == 0) {    // добавление узлов списка, пока не закончится файл, фукция feof возвращает 0, пока не закончится файл,
				add_el(current, input);		  // поэтому её и использовал.
				current = current->next;
				}
			head_res = malloc(sizeof(struct list2));    // память для первого элемента выводного списка
			current = head;
			if (current->n == 'v') {
				head_res->h = vect(current->z, current->size, current->a,
						current->b);
			} else {
				head_res->h = numb(current->z, current->a, current->b);
			}
			head_res->res_next = NULL;
			current = current->next;
			current_res = head_res;
			while (current != NULL) {     // пока элемент списка не последниий
				res_add_el(current_res, current);      // переустановка указателей на следующий элемент
				current = current->next;
				current_res = current_res->res_next;
			}
			current = head;
			current_res = head_res;
			fclose(input);
			output = fopen(out, "w");
			while (current != NULL)       //запись ответа в output
			{
				if (current->n == 'v') {
					fprintf(output, "(");
					for (int i = 0; i < current->size; i++) {
						fprintf(output, " %f", current->a[i]);
					}
					fprintf(output, ") %c (", current->z);
					for (int i = 0; i < current->size; i++) {
						fprintf(output, " %f", current->b[i]);
					}
					fprintf(output, " ) = ");
					if (current->z != '*') {
						fprintf(output, "( ");
						for (int i = 0; i < current->size; i++) {
							fprintf(output, "%f ", current_res->h[i]);
						}
						fprintf(output, ")\n");
					} else {
						fprintf(output, "%f\n", current_res->h[0]);
					}
				} else if (current->n == 's') {
					fprintf(output, " %f %c %f = %f\n", current->a[0],
							current->b[0], current->z, current_res->h[0]);
				}
				current = current->next;
				current_res = current_res->res_next;
			}
			fclose(output);
	}
		printf("Вы хотите продолжить? (y/n)");
		scanf("%s", &e);
	}
	return 0;
}

// каждый блок(функция) калькулятора отдельно написан. Сначала у меня векторный.
float* vect(char z, int size, float *x, float *y) {
	float *res_vect;
	switch (z) {
	case '+':
		res_vect = malloc(size * sizeof(float));
		for (int i = 0; i < size; i++) {
			res_vect[i] = x[i] + y[i];
		}
		return res_vect;
		break;
	case '-':
		res_vect = malloc(size * sizeof(float));
		for (int i = 0; i < size; i++) {
			res_vect[i] = x[i] - y[i];
		}
		return res_vect;
		break;
	case '*':
		res_vect = malloc(sizeof(float));
		res_vect[0] = 0;
		for (int i = 0; i < size; i++) {
			res_vect[0] += x[i] * y[i];
		}
		return res_vect;
		break;
	}
	return x;
	return y;
	free(x);
	free(y);
	free(res_vect);
}

// Теперь обычный.
float* numb(char z, float *a, float *b) {
	float f, m, *res_numb;
	res_numb = malloc(sizeof(float));
	switch (z) {
	case '+':
		res_numb[0] = a[0] + b[0];
		return res_numb;
		break;

	case '-':
		res_numb[0] = a[0] - b[0];
		return res_numb;
		break;

	case '*':
		res_numb[0] = a[0] * b[0];
		return res_numb;
		break;

	case '/':
		if (b != 0) {
			res_numb[0] = a[0] / b[0];
			return res_numb;
		} else {
			return 0;
		}
        break;
	case '!':
		f = 1;
		for (int i = 1; i <= a[0]; i++) {
			f *= i;
		}
		res_numb[0] = f;
		return res_numb;
        break;
	case '^':
		f = 1;
		m = 1;
		for (int i = 1; i <= b[0]; i++) {
			m *= a[0];
		}
		res_numb[0] = m;
		return res_numb;
		break;
	}
	return a;
	return b;
	free(a);
	free(b);
	free(res_numb);
}

//осталось считать указатели и добавить элементы списка. Этот блок считывает указатели и добавляет числа.
float* add_numb(FILE *input, int size) {
	float *numb;
	numb = malloc(size * sizeof(float));
	for (int i = 0; i < size; i++) {
		fscanf(input, "%f", &numb[i]);
	}
	return numb;
}

// добавляю элемент списка для входных данных.
void add_el(struct list1 *current, FILE *input) {
	struct list1 *z = malloc(sizeof(struct list1));
	fscanf(input, " %c", &z->z);
	fscanf(input, " %c", &z->n);
	if (z->n == 'v') {
		fscanf(input, " %i", &z->size);
	} else {
		z->size = 1;
	}
	if (z->z != '!') {
		z->a = add_numb(input, z->size);
		z->b = add_numb(input, z->size);
	} else {
		z->a = add_numb(input, z->size);
		z->b = NULL;
	}
	z->next = NULL;   // последний элемент списка.
	current->next = z;    // переустановка указателя.
}

// добавление элемента списка для выходных данных.
void res_add_el(struct list2 *res_current, struct list1 *current) {
	struct list2 *z_res = malloc(sizeof(struct list1));
	if (current->n == 'v') {
		z_res->h = vect(current->z, current->size, current->a, current->b);
	} else {
		z_res->h = numb(current->z, current->a, current->b);
	}
	z_res->res_next = NULL;
	res_current->res_next = z_res;
}




