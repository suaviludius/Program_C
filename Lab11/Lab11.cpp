#pragma warning(disable : 4996) // îòêëþ÷åíèå îøèáêè c4996
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#define YES 1
#define NO 0
#define M 1000


void HUSCH(char* num);

void main(int argc, char* argv[])
{
	WORD foregroundColor; //цвет слова
	//WORD backgroundColor; //фон слова
	WORD textAttribute;	//атрибут текста

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//HANDLE - дескриптор, т.е. число, с помощью которого можно идентифицировать ресурс. ссылка на графические объекты
	//это номер потока для буфера консоли в системе
	//активный экранный буффер

	foregroundColor = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
	//backgroundColor = BACKGROUND_RED;

	textAttribute = foregroundColor;//| backgroundColor;// цвет текста
	SetConsoleTextAttribute(hStdout, textAttribute);

	FILE* f;
	int i; //
	int j; //
	char* str = (char*)calloc(101, 1); // 

	if (argc == 2)
		strcpy(str, argv[1]);
	while ((f = fopen(str, "r")) == NULL)
	{
		printf("Cannot open input file.\n");
		printf("Please enter a file address: ");
		gets_s(str, 100);
	}

	free(str);
	while (!feof(f)) // for EOF
	{
		str = (char*)calloc(101, 1);
		fgets(str, M, f);
		str = (char*)realloc(str, strlen(str) + 1);
		i = 0;
		while (str[i] != '\0')
		{
			if (str[i] == '/' && str[i + 1] == '/')
			{
				while (str[i] != '\0')
				{
					printf("%c", str[i++]);
				}
				break;
			}
			else if (str[i] == '"')
			{
				i++;
				char* num = (char*)calloc(100, 1);
				j = 0;
				while (str[i] != '"')
				{
					num[j++] = str[i++];
				}
				num = (char*)realloc(num, j + 1);
				i++;
				HUSCH(num);
			}
			else
				printf("%c", str[i++]);
		}
		free(str);
	}
	fclose(f);
}

void HUSCH(char* num)
{
	WORD foregroundColor0;
	WORD foregroundColor1;
	//WORD backgroundColor;   
	WORD textAttribute;

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	foregroundColor0 = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN /*| FOREGROUND_RED*/;
	foregroundColor1 = FOREGROUND_BLUE | COMMON_LVB_UNDERSCORE;
	//backgroundColor =  BACKGROUND_RED;
	//COMMON_LVB_REVERSE_VIDEO --- изменяет на противоположные атрибуты

	printf("\"");
	textAttribute = foregroundColor1;//| backgroundColor;
	SetConsoleTextAttribute(hStdout, textAttribute);
	printf("%s", num);
	textAttribute = foregroundColor0;//| backgroundColor;
	SetConsoleTextAttribute(hStdout, textAttribute);
	printf("\"");
	free(num);
}