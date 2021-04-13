#include <stdio.h>
#include <stdlib.h>


/* работа Клименко Максима: калькулятор с векторами*/
int main()
{
    int size, res;
    long long int g;
    float a, b, *x, *y, h;
    char c, d, e, z, n, in[100], out[100];
    h = 0;
    g = 1;
    /* обозначаю указатели и немного украшаю пользовательский интерфейс*/
    do
    {
        FILE *input, *output;
        printf("\nВведите имя файла для ввода: ");
		scanf("%s", in);
		printf("Введите имя файла для вывода: ");
		scanf("%s", out);
		input = fopen(in, "r");
		output = fopen(out, "w");
        fprintf(output,"Введите, какой калькулятор вы хотите использовать(n нормальный, v векторный): ");
        fscanf(input, " %c", &n);
        switch (n) {
        case 'v':
            fprintf(output, "Введите размер вектора: ");
            fscanf(input, " %i", &size);
            x = malloc(size * sizeof(float));
            y = malloc(size * sizeof(float));
            fprintf(output, "Выберите операцию, которую проведете с векторами(+, -, *): ");
            fscanf(input, " %c", &z);
            /* с помощью кейсов распределяю, когда какой блок будет работать
            1 кейс- обработка сложения векторов
            2 кейс- обработка разности векторов
            3 кейс- скалярное произведение этих векторов
            и в случае ошибки ввода операции программа выведет
            "Выбрана неправильная операция"
            */

            switch (z) {
            case '+':
                fprintf(output, "Введите первый вектор: ");
                for (int i = 0; i < size; i++)
                    fscanf(input, "%f", &x[i]);
                fprintf(output, "Введите второй вектор: ");
                for (int i = 0; i < size; i++)
                    fscanf(input, "%f", &y[i]);
                fprintf(output, "Результат операции с векторами: ");
                for (int i = 0; i < size; i++)
                    fprintf(output, "%f\n", x[i] + y[i]);
                break;
            case '-':
                fprintf(output, "Введите первый вектор: ");
                for (int i = 0; i < size; i++)
                    fscanf(input, "%f", &x[i]);
                fprintf(output, "Введите второй вектор: ");
                for (int i = 0; i < size; i++)
                    fscanf(input, "%f", &y[i]);
                fprintf(output, "Результат операции с векторами: ");
                for (int i = 0; i < size; i++)
                    fprintf(output, "%f\n", x[i] - y[i]);
                break;
            case '*':
                fprintf(output, "Введите первый вектор: ");
                for (int i = 0; i < size; i++)
                    fscanf(input, "%f", &x[i]);
                fprintf(output, "Введите второй вектор: ");
                for (int i = 0; i < size; i++)
                    fscanf(input, "%f", &y[i]);
                fprintf(output, "Результат операции с векторами: ");
                for (int i = 0; i < size; i++)
                    h = h + x[i] * y[i];
                fprintf(output, "%f\n", h);
                break;
            default:
                fprintf(output, "Выбрана неправильная операция");
                break;
            }
            free(x);
            free(y);
            break;
        case 'n':
            fprintf(output, "Введите первое число: "); /*тут у меня чисто оформление пользовательского интерфейса, спрашиваю
            про использование второго числа, чтобы не возникло ошибок с факториалом, может их и так бы не возникло,
            но я немного устал убирать предупреждения и просто решил упростить этот момент */
            fscanf(input, " %f", &a);
            fprintf(output, "Будет ли использоваться второе число\n(если будете искать факториал)?(+/-) ");
            fscanf(input, " %c", &c);
            switch (c) {
            case '+':
                fprintf(output, "Введите это число: ");
                fscanf(input, " %f", &b);
                break;
            case '-':
                fprintf(output, "Вам доступна только операция факториал, выберите эту операцию!\n");
                break;
            default:
                fprintf(output, "Вы не выбрали операцию, запустите программу заново!\n");
                break;
            }
            fprintf(output, "Введите операцию, которую хотите произвести"
                   " с числами(+,-,*,/,!,^)\n(сложение, вычитание,"
                   "умножение, деление, факториал\nили возведение первого числа в степень второго указанного числа)\n"
                   "учтите, что факториал отрицательного числа взять нельзя :");
            fscanf(input, " %c", &d);
            switch (d) /* дальше все просто, кейсами каждую операцию оформляю, какая операция что делает
            описывать долго, нудно и бессмысленно, так как по символу после case все понятно. Но на всякий случай опишу.
            1 кейс - сложение. 2 кейс- вычитание. 3 кейс - умножение. 4 кейс-деление.
            5 кейс-факториал числа. 6 кейс - возведение в степень. */
            {
            case '+':
                fprintf(output, "Результат:%f+%f=%f", a, b, a + b);
                break;
            case '-':
                fprintf(output, "Результат:%f-%f=%f", a, b, a - b);
                break;
            case '*':
                fprintf(output, "Результат:%f*%f=%f", a, b, a * b);
                break;
            case '/':
                fprintf(output, "Результат:%f/%f=%f", a, b, a / b);
                break;
            case '!':
                for (int i = 1; i <= a; i = i + 1) {
                    g = g * i;
                }
                fprintf(output, "Результат:%lli", g);
                break;
            case '^':
                res = 1;
                for (int i = 0; i < b; i = i + 1) {
                    res = res * a;
                }
                fprintf(output, "Результат:%f^%f=%d", a, b, res);
                break;
            default:
                fprintf(output, "Вы не выбрали операцию, запустите программу заново!");
            }
            g=1;
            res=1;
            break;
    }
    fprintf(output, "Хотите ли продолжить?(y - да, n - нет): ");
    fscanf(input, " %c", &e);
    } while (e == 'y');
    return 0;
}
