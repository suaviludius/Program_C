#pragma warning(disable : 4996)
#include <stdio.h>
#include <time.h> 
#include <conio.h> 
#include <stdlib.h> 
#include <math.h>

#define K 13 // ����� ����� ������ �������� �����

#define STR 20 // ����� ������� �������� ������
#define LSTR 260 // ����� �������� �������� �����
char filestr[STR]; // int or char?
char binstr[LSTR]; // int or char?

void KODER(void); // ��������� � ������� �����
void CHANNEL(void); // ������� ������ � ��������
void DECODER(void); // ���������� ������ � ��������

int CONTROL(int i, int j); // ���������� ������������ ����
int DECODLOG(int i); // ���������� ������� ������������� ����

int main(void)
{
	//int filestr[STR]; // int or char? �� ����������� - ������

	FILE *fp; // ����� �������� � ������� "����", ��-� �� ����
	fp = fopen("text.txt", "r");

	if (fp == NULL) // � ��� �����?
	{
		printf("FILE HAS NOT BEEN OPENED");
		return 0;
	}

	fgets(filestr, STR, fp);
	puts(filestr); // uberu
	fclose(fp);

	KODER();

	printf("\n"); // ����� �����
	for (int i = 0, j = 1; i < LSTR; ++i, ++j) // ��� ����
	{
		printf("%d", binstr[i]);
		if (j == K) // uberu
		{
			printf(" %d ", i);
			j = 0;
		}
	}

	printf("\n");

	CHANNEL();
	printf("\n");
	for (int i = 0, j = 1; i < LSTR; ++i, ++j) // ��� ����
	{
		printf("%d", binstr[i]);
		if (j == K) // uberu
		{
			printf(" %d ", i);
			j = 0;
		}
	}

	printf("\n");

	DECODER();
	printf("\n");
	for (int i = 0, j = 1; i < LSTR; ++i, ++j) // ��� ����
	{
		printf("%d", binstr[i]);
		if (j == K) // uberu
		{
			printf(" %d ", i);
			j = 0;
		}
	}

	FILE *fn; // ������� ���������
	fn = fopen("restext.txt", "w");

	fputs(filestr, fn);
	fclose(fn);

	return 0;
}

void KODER(void)
{
	//int MTR[K+1][4]; // MATRIX
	int n; // ����������
	int pos; // ������� �������
	char c; // ������� ������
	int j = 0; // ������� ���� ������ ��������� �� 12 ��������
	int i; // �������

	printf("%c", filestr[0]); // uberu
	printf("%d", filestr[0]); // uberu
	printf("%c\n", filestr[0]); // uberu

								// ������� �������� ��� � ����� ��������

	for (i = 0; (c = filestr[i]) != '\0'; ++i, j = 0)
	{
		printf(" %c ", c); // uberu

		for (n = 0, pos = n + i * K; n < 8; ++n, ++pos, ++j) // � ���� 8 ���, ����� ����� n � ���������� pos
		{
			if (j != 0 && j != 1 && j != 3 && j != 7)
			{
				binstr[pos] = (c >> 7 - n) & 1;
			}
			else
			{
				--n;
				binstr[pos] = 0;
			}
		}
		for (j = 0, pos = i * K; j < K - 1; ++j, ++pos) // -1
		{
			if (j == 0 || j == 1 || j == 3 || j == 7)
			{
				binstr[pos] = CONTROL(i, j); // �������� ����������� ����
			}
		}
		for (j = 0, pos = i * K; j < K - 1; ++j)
		{
			binstr[pos + K - 1] = binstr[pos + K - 1] + binstr[pos + j];
		}
		binstr[pos + K - 1] = binstr[pos + K - 1] & 1; // �������� 1
	}

}

int CONTROL(int i, int j)
{
	int LINE[K - 1]; // ������ ������� �������������� // -1
	int z = j; // ��� ��������
	int x;
	int t = 0;
	int sum = 0;
	int pos = i * K; // ���� ������ ������� �������

	for (x = 0; x < j; ++x)
	{
		LINE[x] = 0;
	}
	x = 1;
	while (z < K - 1) // -1
	{
		if (t == j + 1)
		{
			x = x ^ 1;
			t = 0;
		}
		LINE[z] = x;

		if (x == 1)
		{
			sum = sum + binstr[pos + z];
		}

		++t;
		++z;
	}
	x = sum & 1; // ������� �� ���2
	return x;
}

void CHANNEL(void)
{
	int i; // ��������� ����
	int y = 0; // ����������
	int z = 1; // ����� �������� �����
	int j = 0; // ��������� ������

	FILE *fl; // ��� ��� ����� ������
	fl = fopen("channellog.txt", "w");
	fprintf(fl, "1, 2, 4, 8 ���� - ����������� ���� ������� �������� �����.\n");
	fputs(filestr, fl);
	fprintf(fl, " - �������, ��������� �� ����� text.txt. ����� ������ ������� ����, ��������� �������� KODER (������� ��� ��������, � ����� ������� �� ���):\n");

	for (i = 0; i < LSTR; ++i)
	{
		if (i%K == 0 && i != 0)
		{
			fprintf(fl, "  ");
		}
		fprintf(fl, "%d", binstr[i]);
	}

	srand(time(NULL));

	fprintf(fl, "\n��������� ������ ������� CHANNEL - ��������� ���� (������ �� 1):\n���������:\n"); //  
	for (i = -1, i = i + 1 + rand() % 30; i < LSTR; i = i + 1 + rand() % 30) // ���������� �����
	{
		for (; y <= i; ++y)
		{
			if (y%K == 0 && y != 0)
			{
				if (j == 0)
				{
					fprintf(fl, "��� ");
				}
				fprintf(fl, "- ������ �������� ����� �%d (��������� ������: %d)\n", z, j);
				++z;
				j = 0;
			}
		}
		fprintf(fl, "%d ", i + 1); //
		++j;
		binstr[i] = binstr[i] ^ 1;
	}
	fprintf(fl, "- ������ �������� ����� �%d (��������� ������: %d)\n���� ���������� ������� ����� �� �����������, �� ������ � ��� ���.", z, j);

	fprintf(fl, "\n�������������� ������ ������� ����, ����� ������ ������� CHANNEL (������� ��������� ��� ���������� ���������������� ������� ����):\n");
	for (i = 0; i < LSTR; ++i)
	{
		if (i % K == 0 && i != 0)
		{
			fprintf(fl, "  ");
		}
		fprintf(fl, "%d", binstr[i]);
	}
	fclose(fl);
}


void DECODER(void)
{
	int n; // ����������, � ��� ���� ������������ � � ����� ����� AXIS
	int pos = 0; // ������� �������
	char c; // ������� ������
	int j = 0; // ������� ���� ������ ��������� �� 12 ��������
	int i; // �������
	int num; //������� ������������� ���� � �������
	int schet = 0; //������� �� ����������� �����
	int rem_bin = 0; //���������� 13 ��� �������
	int error[STR] = { 0 }; //������� 2�� ������

	FILE *fz; // ��� ��� ����� ��������
	fz = fopen("decoderlog.txt", "w");
	fprintf(fz, "1, 2, 4, 8 ���� - ����������� ���� ������� �������� �����.\n������ ��������� ����� ���� ����� ���������� �������.\n������ � ������� ������� ����� ������ �� '@'.");
	fprintf(fz, "\n�������������� ������ ������� ����, ����� ������ ������� CHANNEL (������� ��������� ��� ���������� ���������������� ������� ����):\n");
	for (i = 0; i < LSTR; ++i)
	{
		if (i % K == 0 && i != 0)
		{
			fprintf(fz, "  ");
		}
		fprintf(fz, "%d", binstr[i]);
	}

	fprintf(fz, "\n��������� ������ ������� DECODER - ��������������, ��� ��������, ����������� ����� (������ �� 1):\n���������:");
	//fputs(filestr, fz);

	printf(" \n ");
	for (i = 0, n = 1; (c = filestr[i]) != '\0'; ++i)
	{
		rem_bin = 0; // �������� � ������ ����� ���������

		for (j = 0, pos = i * K; j < K - 1; ++j)
		{
			rem_bin = rem_bin + binstr[pos + j]; //������� ����� ��� ��������
		}

		rem_bin = rem_bin & 1; // �������� 1, ������ 0

		num = DECODLOG(i);
		printf("( %d ", rem_bin);
		printf(" %d )", num);

		if (rem_bin == binstr[pos + K - 1] && num >= 0) //2 ������ (�� ���� ������ ����������� ������, �� ��� ����)
		{
			error[i] = 1; //����� ����� ��������� ������ � ������� � ������� i
			fprintf(fz, "\n� ������� ����� � %d ���������� ������� ������.", n);
			++n;
		}

		else if (num >= 0 && num < 12) // 1 ������ 
		{
			binstr[i * K + num] ^= 1; //������������ ��� ������ �� ����������
			fprintf(fz, "\n� ������� ����� � %d ���������� ����������� ������. ������������ ������ - %d.", n, i*K + num + 1);
			++n;
		}
		if (n == i + 1)
		{
			fprintf(fz, "\n� ������� ����� � %d ������ �� ����������.", n);
			++n;
		}
	}

	printf(" \n ");

	for (i = 0; (c = filestr[i]) != '\0'; ++i, j = 0)
	{
		if (error[i] == 1) // ��������� �� ��, ��� � ����� 2 ������
		{
			filestr[i] = '@'; //���������� ������ � ��������
			printf(" %c ", filestr[i]);
			continue;
		}

		schet = 0; // ��� ����� ������� �������� ������� �� ����������� �����
		c = 0; // �������� ��� �������� �������, ����� �������� ��� ������

		for (j = 0, pos = i * K; j < K - 1; ++j, ++pos) // -1
		{
			if (j != 0 && j != 1 && j != 3 && j != 7)
			{
				c = c + pow(2, (7 - schet))*binstr[pos]; //��������� ��� ������� �� 2�� � 10��
				schet++; //���������� �� ����������� ���
			}
		}

		filestr[i] = c; //���������� ������ � ��������
		printf(" %c ", filestr[i]);
	}

	fprintf(fz, "\n��������� ������� �� ������������, �.�. ��� ����� ������, ����� ������� ����� ������ �� �������� � %d �� ����� �����-���� ����������.\n�������������� ������ ������� ����, ����� ������ ������� DECODER (������� ��������� ��� ���������� ���������������� ������� ����):\n", n - 1);
	for (i = 0; i < LSTR; ++i)
	{
		if (i % K == 0 && i != 0)
		{
			fprintf(fz, "  ");
		}
		fprintf(fz, "%d", binstr[i]);
	}
	fprintf(fz, "\n���������:");
	fputs(filestr, fz);
	fclose(fz);
}

int DECODLOG(int i)

{
	int schet = 0; // ������� ��������
	int pos = 0; //������� �������
	int j = 0; //����� ���� � �������
	int  num = 0; //����� ������� ���� ---> �� ��� ����� <---
	int cret = 3; //������� ����� ������ ����������� ����������� ����� (4 �����������, �.�. � ����� ������� ������ 8 ���)	

	for (j = 0, pos = i * K; j < 8; ++j, ++pos)
	{

		if (j == 0 || j == 1 || j == 3 || j == 7) //����������� ������� ���������
		{
			schet *= 10; //����� ������� ��������
			schet += CONTROL(i, j); //������� ��������� (������ ������) � ���������� ����� ����� ����� ������������� ��������!!!
		}

		if (j == 7)//����� ������������� ������� ����� ��������� ���������� ������������ ����
		{
			while (schet) //���������� ������� ������������� ���� � �������
						  // ������� ����� �������, �.�. ���������� ������� ����� �������
			{
				num += pow(2, cret)*(schet % 10);
				schet = schet / 10;
				cret--;
			}

			return (num - 1); //�.�. ���� � ������ �� 0, � �� �� 1

		}
	}
}