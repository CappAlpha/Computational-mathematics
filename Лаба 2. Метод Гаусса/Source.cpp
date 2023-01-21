#include <iostream>
using namespace std;

// ¬ывод системы уравнений
void sysout(double* a, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%8.2f", a[i * m + j]);
        }
        printf("\n");
    }
}

void gauss(double* a, double* b, int n)
{
    double c;
    int i, j, k;
       /*пр€мой ход */
            for (i = 0; i < n; i++)
            {      
                for (j = i + 1; j < n; j++)
                {
                    c = a[j * n + i] / a[i * n + i];
                    for (k = i; k < n; k++)
                        a[j * n + k] -= c * a[i * n + k];
                    b[j] -= c * b[i];
                }
            }
        /*обратный ход*/
        for (i = n; i >= 0; i--)
        {        
            for (j = i + 1; j < n; j++)
                b[i] -= a[i * n + j] * b[j];
            b[i] /= a[i * n + i];
        }
    }

    int main()
    {
        double A[4][4] = {3, 6, 8, 9, 4, 7, 9, 1, 2, 5, 6, 7, 1, 2, 3, 4}, B[4][1] = { 65, 57, 49, 25 };

        printf("   A\n");
        sysout(&A[0][0], 4, 4);
        printf("\n   B\n");
        sysout(&B[0][0], 4, 1);

        gauss(&A[0][0], &B[0][0], 4);

        printf("\n   X\n");
        sysout(&B[0][0], 4, 1);
        getchar();
    }