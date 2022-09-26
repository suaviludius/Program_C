#include <stdio.h> 
#include <conio.h> 
#include <locale.h> 
int main()
{
	int solo = 0;
	int x = 0;
	unsigned long t = 0b0;
	int temp = 0; //переменная для сравнения
	unsigned int res_x = 0;

	
	setlocale(LC_ALL, "Rus");
	printf("Введите чиселко х: "); //ввод числа в 16 ричной форме
	scanf_s("%x", &x);
	res_x = (unsigned int)x;
	

	
	printf("Ввод:  ");
	for (int i = 0; i < sizeof(res_x) * 8; i++) 
	{ 
		
		temp = res_x; 
		res_x <<= 1; 
		res_x >>= 1;
		if (res_x == temp)
			printf("0");
		else
		{
			printf("1");
			solo++;
		}
		if ((i + 1) % 8 == 0) 
		{
			printf(" ");
			for (int n = i-7; n < i-7+solo; n++)
			{
				t = t | (1 << 31-n);
			}
			solo = 0;
		}
		
		res_x <<= 1; 
	}

	printf("\nВывод: ");

	for (int i = 0; i < sizeof(t) * 8; i++) //где сайзоф это разряды в битах одной 16ричной цифры
	{
		temp = t; // присваиваем переменной значение числа
		t <<= 1;
		t >>= 1;
		// обнулили последний(левый) бит числа
		if (t == temp)// если число при этом не изменилось, то значит там стоял "0", иначе "1"
			printf("0");
		else
			printf("1");

		if ((i + 1) % 8 == 0) // ставим разделитель после 8 бит (для удобства просмотра)
		{
			printf(" ");
		}

		t <<= 1; //сдвигаем на бит влево (убираем самый левый бит, в конец строчки добавляем "0")
	}


	return 0;
}
