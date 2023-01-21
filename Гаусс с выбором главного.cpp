#include <iostream>
using namespace std;

// ����� ������� ���������
void sysout(double** a, double* b, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << "*x" << j;
            if (j < n - 1)
                cout << " + ";
        }
        cout << " = " << b[i] << endl;
    }
    return;
}
double* gauss(double** a, double* b, int n)
{
    double* x, max;
    int k, index;
    const double eps = 0.00001;  // ��������
    x = new double[n];
    k = 0;
    while (k < n)
    {
        // ����� ������ � ������������ a[i][k]
        max = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++)
        {
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);
                index = i;
            }
        }
        // ������������ �����
        if (max < eps)
        {
            // ��� ��������� ������������ ���������
            cout << "������� �������� ���������� ��-�� �������� ������� ";
            cout << index << " ������� A" << endl;
            return 0;
        }
        for (int j = 0; j < n; j++)
        {
            double temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }
        double temp = b[k];
        b[k] = b[index];
        b[index] = temp;
        // ������������ ���������
        for (int i = k; i < n; i++)
        {
            double temp = a[i][k];
            if (abs(temp) < eps) continue; // ��� �������� ������������ ����������
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / temp;
            b[i] = b[i] / temp;
            if (i == k)  continue; // ��������� �� �������� ���� �� ����
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            b[i] = b[i] - b[k];
        }
        k++;
    }
    // �������� �����������
    for (k = n - 1; k >= 0; k--)
    {
        x[k] = b[k];
        for (int i = 0; i < k; i++)
            b[i] = b[i] - a[i][k] * x[k];
    }
    return x;
}
int main()
{
    double** a, * b, * x;
    int n;
    system("chcp 1251");
    system("cls");
    cout << "������� ���������� ���������: ";
    cin >> n;
    a = new double* [n];
    b = new double[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            cout << "a[" << i << "][" << j << "]= ";
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << "b[" << i << "]= ";
        cin >> b[i];
    }
    sysout(a, b, n);
    x = gauss(a, b, n);
    for (int i = 0; i < n; i++)
        cout << "x[" << i << "]=" << x[i] << endl;
    cin.get(); cin.get();
    return 0;
}