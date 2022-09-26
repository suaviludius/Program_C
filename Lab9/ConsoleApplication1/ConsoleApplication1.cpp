#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define N 180

int main(int argc, char* argv[])
{
	FILE* f;
	int simv = 0; //Счетчик колличества одинаковых символов 
	char arr[N]; // Массив символов файла
	int rat[N] = { 0 }; // Массив колличества повторений символов
	int k = 0; //количество символов в файле
	char filename[100] = { 0 };

	printf("Please enter a file address or enter a number from 1 to 3 to open the default file: ");
	gets_s(filename);
	if (filename[0] == 0)
	{
		printf("If there is no input value, the default file will be taken.\n");
		printf("Please enter a file address: ");
		gets_s(filename);
	}

	int n = 9;
	srand(time(NULL));
	if ((f = fopen((filename[0] == 0 ? argv[n = rand() % 3 + 1] : filename[0] == '1' ? argv[n = 1] : filename[0] == '2' ? argv[n = 2] : filename[0] == '3' ? argv[n = 3] : filename), "r")) == NULL) //Открытие файла для чтения
	{
		printf("Cannot open input file.\n");
		return 1;
	}
	printf("Item selected: %s\n", n == 0 ? argv[n] : n == 1 ? argv[n] : n == 2 ? argv[n] : n == 3 ? argv[n] : filename);

	while ((arr[k] = fgetc(f)) != EOF) k++; //Заносим символы файла в массив

	FILE* fpout;
	fpout = fopen("D:\\Statistic\\Statistic.txt", "w");
		fprintf(fpout,"Statistics by text file: \n"); //"Статистика по текстовому файлу"
		for (int t = 0; t < k + 1; t++, simv = 0) //Просмотр символов массива символов
		{
			char ch = arr[t]; //символ для сравнения
			for (int i = 0; i < t + 1; i++)// Элементы до символа
			{
				if (ch == arr[i])
				{
					simv++;
				}
			}
			if (simv > 1) continue;
			for (int i = t + 1; i < k; i++) // Элементы после символа
			{
				if (ch == arr[i]) simv++;
			}
			if (ch == '\n') fprintf(fpout, "Symbol  \\n: %3i/%i time \n ", simv, k); else // Новая строка
				if (ch == '\t') fprintf(fpout, "Symbol  \\t: %3i/%i  time\n", simv, k); else // Табуляция
					if (ch == -1) fprintf(fpout, "Symbol EOF: %3i/%i time\n", simv, k); else //Символ конца файла
						fprintf(fpout, "Symbol %3c: %3i/%i time\n", ch, simv, k); // Символ и его количество
			rat[t] = simv; //Запоминаем колличество символов, встретившихся впервые, с номером их расположения в arr[]
		}
	fclose(fpout);

	printf("Character output by frequency: \n"); //"Вывод символов по частоте"
	for (int i = k; i > -1; i--)
	{
		if (rat[i] > 0)
		{
			for (int t = 0; t < i; t++)
			{
				if (rat[i] < rat[t])
				{
					int rat_swap = rat[i]; //своп
					rat[i] = rat[t];
					rat[t] = rat_swap;

					char arr_swap = arr[t]; //пинг
					arr[t] = arr[i];
					arr[i] = arr_swap;
				}
			}
			if (arr[i] == '\n') printf("\\n"); else
				if (arr[i] == '\t') printf("\\t"); else
					if (arr[i] == -1) printf("EOF"); else
						printf("%c", arr[i]);
		}
	}
	printf("\n");
	fclose(f);
	return 0;
}
