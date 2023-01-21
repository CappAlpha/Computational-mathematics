#include <stdio.h>
#include <math.h>
#include <iostream>
#include <locale.h>

using namespace std;

double skal(double*, int, int);
void mult(double*, double*, double*, int, int, int);

int iter = 0;

void mult(double* x, double* y, double* z, int n, int m, int k)
{
	int i, j, h;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			z[i * m + j] = 0;
			for (h = 0; h < k; h++)
			{
				z[i * m + j] += x[i * k + h] * y[h * m + j];
			}
		}
	}
}

double skal(double* m, int a, int b)
{
	int i;
	double d, s1, s2, t = 1, l1 = 0, l0 = 0, e = 0.000001,
		* y, * y_n;

	y = (double*)calloc(b, sizeof(double));
	y_n = (double*)calloc(b, sizeof(double));

	while (t >= e)
	{
		d = 0;
		s1 = 0;
		s2 = 0;

		//нахождение y
		if (iter != 0)
		{
			mult(y_n, m, y, 1, b, b);
		}
		else
		{
			for (i = 0; i < b; i++)
				y[i] = 1;
		}

		//нахождение d
		for (i = 0; i < b; i++)
			d += y[i];
		d = sqrt(d);

		if (iter != 0)
		{
			//нахождение s1
			for (i = 0; i < b; i++)
			{
				s1 += y[i] * y[i];
			}

			//нахождение s2
			for (i = 0; i < b; i++)
			{
				s2 += y[i] * y_n[i];
			}

			//нахождение собственного числа l
			l1 = s1 / s2;

			//нахождение точности
			t = abs(l1 - l0) / l1;

			l0 = l1;
			iter++;
		}

		//нахождение y нормированный
		for (i = 0; i < b; i++)
			y_n[i] = y[i] / d;

		iter++;
	}

	return l1;
}

int main()
{
	setlocale(LC_ALL, "rus");

	int n = 4;
	double l, a[4][4] = { { 1, 2, 2, 1 }, { 2, 3, 4, 3}, { 2, 4, 3, 1}, { 1, 3, 1, 1} };

	cout << "Исходная матрица:" << endl << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << "\t" << a[i][j];
		}
		cout << endl;
	}

	l = skal(&a[0][0], n, n);
	cout << endl << "Собственное число:\t" << l << endl << endl;

	cout << "Количество итераций:\t" << iter << endl << endl;
	getchar();
}