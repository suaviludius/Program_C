#pragma warning(disable:4996)
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define N 100
#define M 50
int main(int argc, char* argv[]) {
	FILE* f;
	char filename[100] = { 0 }; //имя файла
	//
	int all = 0;//кол-во символов в тексте(без EOF)
	int max_j = 0;//максимальная длина строки в тексте
	int now_j = 0;//текущая длина строки
	int j = 0, k = 0;// позиции элементов в массиве а
	//
	long int alfa = 0;//сумма символов строки
	long int beta = 0;//сумма символов строки сравниваемой с первой
	char ch_gag; //символ рассматриваемой строки
	char ch; // Текущий символ

	//Проверяем на наличие аргументов по умолчанию
	if (argc == 2)
		strcpy(filename, argv[1]);
	else {
	tr:
		printf("Please enter a file address: ");
		gets_s(filename);
	}
	if ((f = fopen(filename, "r")) == NULL) //Открытие файла для чтения
	{
		printf("Cannot open input file.\n");
		goto tr; // Повторяем, пока пользователь не умрет или не захочет выпить
	}

	// а  – массив указателей на выделенный участок памяти под массив вещественных чисел типа char
	char** a = new char* [N]; // N строк в массиве
	for (int i = 0; i < N; i++)
		a[i] = new char[M]; // и M столбцов
	char* pre_a = new char[1000]; //1-ый массив текстового ф-ла 

	while ((pre_a[all] = fgetc(f)) != EOF)
	{
		now_j++;
		if (*(pre_a+all) == '\n') {
			if (now_j > max_j) max_j = now_j;
			now_j = 0;
		}
		all++;
	}
	pre_a[all++] = -1;
	fclose(f);

	for(char* gr = pre_a; gr < pre_a + all + 1; gr++)//Заносим в двумерный массив строки по одномерному(заполняя пустые места пробелами)
	{
		if (*gr != -1 && *gr != 10)
		{
			a[k][j++] = *gr;
		}
		else
		{
			if (j < max_j)
				for (int tea = j; tea < max_j; tea++)
					a[k][tea] = ' ';
			k++; j = 0;
		} 
	}
	delete[] pre_a; // очистка памяти

	for (int i = 0; i < k-1; i++)
	{	
		for (int e = i + 1; e < k; e++) // проход по строкам ниже исходной
		{

			for (int t = 0, ps_t = 0; t < max_j, ps_t < max_j; t++, ps_t++)// проход по столбцам
			{
				while (*(*(a + i) + t) == ' ') t++;
				while (*(*(a + e) + ps_t) == ' ') ps_t++;
				int ch = *(*(a + i) + t);
				int ch_gag = *(*(a + e) + ps_t);
				alfa += tolower(ch);
				beta += tolower(ch_gag);

				if (alfa > beta) 
				{
					for (int juy = 0; juy < max_j; juy++)
					{
						int swap = a[e][juy];
						a[e][juy] = a[i][juy];
						a[i][juy] = swap;
					}
					break;
				}
				if (alfa < beta) break;
			}
			alfa = beta = 0;
		}
	}

	FILE* fpout;
	fpout = fopen("D:\\Statistic\\Crocodile.txt", "w");
	for (int i = 0; i < k; i++)
	{
		for (int t = 0; t < max_j; t++) 
		{
			fprintf(fpout, "%c", *(*(a+i)+t));
		}
		fprintf(fpout, "\n");
	}
	fclose(fpout);
	// высвобождение памяти отводимой под двумерный динамический массив:
	for (int i = 0; i < N; i++)
		delete[] a[i];
	// где N – количество строк в массиве
}