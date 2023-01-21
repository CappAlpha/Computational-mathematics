#include <iostream>
#include <math.h>

using namespace std;

void main()
{
	int i, j, k, p, iter = 0, n = 4;
	double e = 0.001, t = 100, max = 100,
		A[4][4] = {{8, 1, 1, 2}, {1, 4, 1, 1}, {1, 1, 3, 1}, {2, 1, 1, 6}},
		B[4] = {33, 13, 18, 23},
	    A0[4][4], B0[4], x0[4], x[4];

	setlocale(LC_ALL, "Russian");

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			A0[i][j] = -(A[i][j] / A[i][i]);
		}
	}

	for (i = 0; i < n; i++)
	{
		B0[i] = B[i] / A[i][i];
		A0[i][i] = 0;
		x0[i] = B0[i];
	}

	while (max >= e)
	{
		for (i = 0; i < n; i++)
		{
			x[i] = 0;
			for (j = 0; j < n; j++)
			{
				x[i] += A0[i][j] * x0[j];
			}
		}
		for (i = 0; i < n; i++)
		{
			x[i] += B0[i];
		}

		max = 0;

		for (i = 0; i < n; i++)
		{
			t = abs((x[i] - x0[i]) / x[i]);
			if (t > max)
			{
				max = t;
			}
			x0[i] = x[i];
		}
		iter++;
	}

	cout << "Корни системы" << endl;
	for (i = 0; i < n; i++)
	{
		cout << "x[" << i + 1 << "] = ";
		printf_s("%0.3f\n", x[i]);
	}

	cout << "Количество итераций  " << iter << endl;
}
