// Работа Клименко Максима. Стек.
//Были использованы части кода со страницы https://learnc.info/adt/stack.html
//Сайт называется "Реализация стека на С"
//Я просто подключаю файлы, и дополняю своим калькулятором
//При сборке ошибок не возникало
//Пример ввода входных данных: 2 1 + 7 * 2 - n (в конце каждого выражения прописать "n")
#include <stdio.h>
#include <stdlib.h>
typedef struct element {
	float data;
	struct element *next;
} stack;
stack *head_stack = NULL;
void push_element(stack **head, float data);/* описание функций, которые у меня используются*/
float pop_element(stack **head);
float numb(char sign, float x, float y);
int main(int argc, char *argv[]) {
	char n = 'y', str[20], t = '0';
	char in[20], out[20];
	int i = 0;
	float num, x, y;
	FILE *input, *output;
	while (n == 'y') {
		printf("Enter name of input file:"); // запрос, как назвать файлы при каждом запуске
		scanf(" %s", in);
		printf("Enter name of output file:");
		scanf(" %s", out);
		input = fopen(in, "r");
		output = fopen(out, "w");
		while (feof(input) == 0) {
			fscanf(input, "%c", &str[i]);
			if (str[i] == ' ') {
				if (t == '0') { //ищет пробелы
					num = strtof(str, NULL); // разделяет строку на отдельные элементы
					push_element(&head_stack, num);
					i = 0;
				}
			} else if (str[i] == '*' || str[i] == '+' || str[i] == '-' //ищет операцию, затем выполняется эта операция с найденными элементами
					|| str[i] == '/' || str[i] == '^') {
				y = pop_element(&head_stack);
				x = pop_element(&head_stack);
				push_element(&head_stack, numb(str[i], x, y));
				fprintf(output, "%.2f  ", numb(str[i], x, y));
				t = '1';
			} else if (str[i] == 'n') { //ищет элемент, который прервёт выполнение функции
				while (head_stack != NULL)
					pop_element(&head_stack);
				fprintf(output, "\n");
			} else {
				t = '0';
				i = i + 1;
			}
		}
		fclose(input);
		fclose(output);
		printf("Хотите ли вы продолжить (y/n)"); //запрос на продолжение работы
		scanf(" %c", &n);
	}
	return 0;
}
float numb(char sign, float x, float y) { //сам калькулятор
	float res, f, S;
	switch (sign) {
	case '+':
		res = x + y;
		return res;
		break;
	case '-':
		res = x - y;
		return res;
		break;
	case '*':
		res = x * y;
		return res;
		break;
	case '/':
		if (y != 0)
			res = x / y;
		return res;
		break;
	case '!':
		f = 1;
		for (int i = 1; i <= x; i++) {
			f *= i;
		}
		res = f;
		return res;
	case '^':
		f = 1;
		S = 1;
		for (int i = 1; i <= y; i++) {
			S *= x;
		}
		res = S;
		return res;
	}
	return x;
	return y;
}

void push_element(stack **head, float data) { //кладёт элемент на вершину стека
	stack *z = malloc(sizeof(stack));
	z->next = *head;
	z->data = data;
	*head = z;
}

float pop_element(stack **head) { //снимает элемент с вершины стека, перемещая вершину к следующему элементу.
	stack *z;
	float data;
	z = *head;
	*head = (*head)->next;
	data = z->data;
	return data;
}
