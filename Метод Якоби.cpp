#include <stdio.h>
#include <iostream>
#include <math.h>

const double PI = 3.1415926536;

bool isSimmetrial(double** coefficients, int numberOfEquation) 
{
	bool iter = true;
	int i, j;
	for (i = 0; i < numberOfEquation; i++) 
	{
		for (j = i + 1; j < numberOfEquation; j++) 
		{
			if (coefficients[i][j] != coefficients[j][i]) 
			{
				iter = false;
				break;
			}
		}
		if (!iter) { break; }
	}
	return iter;
}
int wrachenie(double** coefficients, int numberOfEquation, double** solution, double e)
{
	int iter = 1;
	int i, j, k;
	int maxI, maxJ;
	double max, fi;
	double** V; // матрица поворота
	V = new double* [numberOfEquation];
	for (i = 0; i < numberOfEquation; i++) 
	{
		V[i] = new double[numberOfEquation];
	}
	double** temp;
	temp = new double* [numberOfEquation];
	for (i = 0; i < numberOfEquation; i++)
	{
		temp[i] = new double[numberOfEquation];
	}
	double t = 0.0;
	for (i = 0; i < numberOfEquation; i++) 
	{
		for (j = i + 1; j < numberOfEquation; j++)
		{
			t = t + coefficients[i][j] * coefficients[i][j];
		}
	}
	t = sqrt(2 * t);
	while (t > e)
	{
		max = 0.0;
		for (i = 0; i < numberOfEquation; i++) 
		{
			for (j = i + 1; j < numberOfEquation; j++) 
			{
				if (coefficients[i][j] > 0 && coefficients[i][j] > max) 
				{
					max = coefficients[i][j];
					maxI = i;
					maxJ = j;
				}
				else if (coefficients[i][j] < 0 && -coefficients[i][j] > max)
				{
					max = -coefficients[i][j];
					maxI = i;
					maxJ = j;
				}
			}
		}
		for (i = 0; i < numberOfEquation; i++) 
		{
			for (j = 0; j < numberOfEquation; j++)
			{
				V[i][j] = 0;
			}
			V[i][i] = 1;
		}
		if (coefficients[maxI][maxI] == coefficients[maxJ][maxJ]) 
		{
			V[maxI][maxI] = V[maxJ][maxJ] = V[maxJ][maxI] = sqrt(2.0) / 2.0;
			V[maxI][maxJ] = -sqrt(2.0) / 2.0;
		}
		else 
		{
			fi = 0.5 * atan((2.0 * coefficients[maxI][maxJ]) / (coefficients[maxI][maxI] - coefficients[maxJ][maxJ]));
			V[maxI][maxI] = V[maxJ][maxJ] = cos(fi);
			V[maxI][maxJ] = -sin(fi);
			V[maxJ][maxI] = sin(fi);
		}
		for (i = 0; i < numberOfEquation; i++)
		{
			for (j = 0; j < numberOfEquation; j++)
			{
				temp[i][j] = 0.0;
			}
		}
		for (i = 0; i < numberOfEquation; i++) 
		{
			for (j = 0; j < numberOfEquation; j++)
			{
				for (k = 0; k < numberOfEquation; k++) 
				{
					temp[i][j] = temp[i][j] + V[k][i] * coefficients[k][j];
				}
			}
		}
		for (i = 0; i < numberOfEquation; i++) 
		{
			for (j = 0; j < numberOfEquation; j++) 
			{
				coefficients[i][j] = 0.0;
			}
		}
		for (i = 0; i < numberOfEquation; i++) 
		{
			for (j = 0; j < numberOfEquation; j++) 
			{
				for (k = 0; k < numberOfEquation; k++) 
				{
					coefficients[i][j] = coefficients[i][j] + temp[i][k] * V[k][j];
				}
			}
		}
		t = 0.0;
		for (i = 0; i < numberOfEquation; i++)
		{
			for (j = i + 1; j < numberOfEquation; j++) 
			{
				t = t + coefficients[i][j] * coefficients[i][j];
			}
		}
		t = sqrt(2 * t);
		for (i = 0; i < numberOfEquation; i++) 
		{
			for (j = 0; j < numberOfEquation; j++) 
			{
				temp[i][j] = 0.0;
			}
		}
		for (i = 0; i < numberOfEquation; i++) {
			for (j = 0; j < numberOfEquation; j++) 
			{
				for (k = 0; k < numberOfEquation; k++) 
				{
					temp[i][j] = temp[i][j] + solution[i][k] * V[k][j];
				}
			}
		}
		for (i = 0; i < numberOfEquation; i++) 
		{
			for (j = 0; j < numberOfEquation; j++) 
			{
				solution[i][j] = temp[i][j];
			}
		}
		iter++;
	}
	return iter;
}

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	int i, j, n;
	double e = 0.000001;
	double** coefficients, ** solution;
	cout << "\nВведите размерность матрицы: ";
	cin >> n;
	cout << "\nВведите элементы матрицы: \n";
	coefficients = new double* [n];
	solution = new double* [n];
	for (i = 0; i < n; i++) 
	{
		coefficients[i] = new double[n];
		solution[i] = new double[n];
	}
	for (i = 0; i < n; i++) 
	{
		for (j = 0; j < n; j++) 
		{
			solution[i][j] = 0;
		}
		solution[i][i] = 1;
	}
	for (i = 0; i < n; i++) 
	{
		cout << "Введите " << i + 1 << " строку: ";
		for (j = 0; j < n; j++) 
		{
			cin >> coefficients[i][j];
		}
	}
	if (!isSimmetrial(coefficients, n)) 
	{
		cout << "\nМатрица не симметричная";
	}
	else {
		int iter = wrachenie(coefficients, n, solution, e);
		for (i = 0; i < n; i++) 
		{
			cout << "\nСобственный вектор x " << i + 1 << ":\n";
			for (j = 0; j < n; j++) 
			{
				cout << solution[j][i] << "\n";
			}
		}
		cout << "\nСобственные значения:\n";
		for (i = 0; i < n; i++) 
		{
			cout << coefficients[i][i] << "\n";
		}
		cout << "\nКоличество итераций: " << iter;
	}
	getchar();
}