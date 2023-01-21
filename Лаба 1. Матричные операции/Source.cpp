#include <iostream>
#include <math.h>

using namespace std;

void m_transp(double*, double*, int, int);
void m_umnMatr(double*, double*, double*, int, int, int);
void m_umnK(double*, double*, int, int, double);
void m_razn(double*, double*, double*, int, int);
void m_sum(double*, double*, double*, int, int);
void m_print(double*, int, int);
void m_check(double*, double*, int, int, int, int);

void main()
{
	double N[2][4] = { {1, 2, 3, 9}, {8, 6, 0, 1} },
	    K[4][4] ={{1,2,3,4},{2,3,4,5},{3,4,5,6},{4,5,6,7}},
		*M, * MN, * Kt, * kKt, * C;

	M = (double*)calloc(4 * 4, sizeof(double));
	MN = (double*)calloc(4 * 4, sizeof(double));
	Kt = (double*)calloc(4 * 4, sizeof(double));
	kKt = (double*)calloc(4 * 4, sizeof(double));
	C = (double*)calloc(4 * 4, sizeof(double));

	m_transp(&N[0][0], M, 2, 4);
	cout << "M =  ";
	m_print(M, 4, 2);

	m_transp(&K[0][0], Kt, 4, 4);
	cout << "Kt =  ";
	m_print(Kt, 4, 4);

	m_umnMatr(M, &N[0][0], MN, 4, 4, 2);
	cout << "MN =  ";
	m_print(MN, 4, 4);

	m_umnK(Kt, kKt, 4, 4, 3);
	cout << "3Kt =  ";
	m_print(kKt, 4, 4);

	m_razn(kKt, MN, C, 4, 4);
	cout << "C =  ";
	m_print(C, 4, 4);

	m_check(MN, Kt, 4, 4, 4, 4);

	free(M);
	free(MN);
	free(Kt);
	free(kKt);
	free(C);

	getchar();
}

void m_transp(double* x, double* y, int n, int m)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			y[j * n + i] = x[i * m + j];
		}
	}
}

void m_umnMatr(double* x, double* y, double* z, int n, int m, int k)
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

void m_umnK(double* x, double* y, int n, int m, double k)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			y[i * m + j] = x[i * m + j] * k;
		}
	}
}

void m_razn(double* x, double* y, double* z, int n, int m)
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			z[i * n + j] = x[i * n + j] - y[i * n + j];
		}
	}
}

void m_sum(double* x, double* y, double* z, int n, int m)
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			z[i * n + j] = x[i * n + j] + y[i * n + j];
		}
	}
}

void m_print(double* x, int n, int m)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			cout << "\t" << x[i * m + j];
		}
		cout << "\n";
	}
	cout << "\n";
}

void m_check(double* x, double* y, int n, int m, int r, int l)
{
	if ((n == r) || (m == l))
	{
		int i, j;
		double k = 0;
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < n; j++)
			{
				k += abs(x[i * n + j] - y[i * n + j]);
			}
		}
		if (k == 0)
			cout << "Matr sovpadayut";
		else
			cout << "Matr ne sovpadayut";
	}
	else
		cout << "Matr ne sovpadayut";
}
