#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include <iomanip>

using namespace std;

void inversMatrix(double**, int);
void printMatrix(double**, int);
void deleteMatrix(double**, int);
double** allocatMatrix(int);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введите размер матрицы: ";
    cin >> N;

    double** A = allocatMatrix(N);

    for (int i = 0; i < N; i++)
        A[i] = new double[N];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            cout << "a[" << i << "][" << j << "] = ";
            cin >> A[i][j];
        }

    printMatrix(A, N);
    inversMatrix(A, N);

    cout << "\n\n";
    cout << "Обратная матрица: " << "\n\n";
    printMatrix(A, N);

    deleteMatrix(A, N);

    cin.get();
    return 0;
}
void inversMatrix(double** A, int N)
{
    double temp;
    double** E = allocatMatrix(N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            E[i][j] = 0.0;

            if (i == j)
                E[i][j] = 1.0;
        }

    for (int k = 0; k < N; k++)
    {
        temp = A[k][k];

        for (int j = 0; j < N; j++)
        {
            A[k][j] /= temp;
            E[k][j] /= temp;
        }

        for (int i = k + 1; i < N; i++)
        {
            temp = A[i][k];

            for (int j = 0; j < N; j++)
            {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    for (int k = N - 1; k > 0; k--)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            temp = A[i][k];

            for (int j = 0; j < N; j++)
            {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = E[i][j];

    deleteMatrix(E, N);
}
void printMatrix(double** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << setw(8) << setprecision(3) << setiosflags(ios::fixed | ios::showpoint) << matrix[i][j];
        cout << "\n";
    }
}
void deleteMatrix(double** matrix, int n)
{
    for (int i = 0; i < n; i++)
        delete[] matrix[i];

    delete[] matrix;
}
double** allocatMatrix(int n)
{
    double** A = new double* [n];

    for (int i = 0; i < n; i++)
        A[i] = new double[n];
    return A;
}