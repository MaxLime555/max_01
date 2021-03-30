#include <stdio.h>
#include <stdlib.h>
/* работа Клименко Максима: калькулятор с векторами*/
int main()
{
    int size;
    float *a, *b, *res, h;
    char c, d;
    h = 0;
    /* обозначаю указатели и немного украшаю пользовательский интерфейс*/
    a = malloc(size * sizeof(int));
    b = malloc(size * sizeof(int));
    res = malloc(size * sizeof(int));
    do
    {
        printf("Введите размер вектора: ");
        scanf(" %i", &size);
        printf("Выберите операцию, которую проведете с векторами(+, -, *): ");
        scanf(" %c", &c);
        /* с помощью кейсов распределяю, когда какой блок будет работать
    1 кейс- обработка сложения векторов
    2 кейс- обработка разности векторов
    3 кейс- скалярное произведение этих векторов
    и в случае ошибки ввода операции программа выведет
    "Выбрана неправильная операция"
    */
        switch (c) {
        case '+':
            printf("Введите первый вектор: ");
            for (int i = 0; i < size; i++)
                scanf("%f", &a[i]);
            printf("Введите второй вектор: ");
            for (int i = 0; i < size; i++)
                scanf("%f", &b[i]);
            printf("Результат операции с векторами: ");
            for (int i = 0; i < size; i++)
                printf("%f\n", a[i] + b[i]);
            break;
        case '-':
            printf("Введите первый вектор: ");
            for (int i = 0; i < size; i++)
                scanf("%f", &a[i]);
            printf("Введите второй вектор: ");
            for (int i = 0; i < size; i++)
                scanf("%f", &b[i]);
            printf("Результат операции с векторами: ");
            for (int i = 0; i < size; i++)
                printf("%f\n", a[i] - b[i]);
            break;
        case '*':
            printf("Введите первый вектор: ");
            for (int i = 0; i < size; i++)
                scanf("%f", &a[i]);
            printf("Введите второй вектор: ");
            for (int i = 0; i < size; i++)
                scanf("%f", &b[i]);
            printf("Результат операции с векторами: ");
            for (int i = 0; i < size; i++)
                h = h + a[i] * b[i];
            printf("%f\n", h);
            break;
        default:
            printf("Выбрана неправильная операция");
            break;
        }
        printf("Хотите продолжить?(y/n):");
        scanf(" %c", &d);
    } while (d == 'y');
    return 0;
    /* код небольшой, но даже проще, чем обычный для работы с числами, мне понравилось :)   */
}
