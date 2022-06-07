#include <iostream>
#include <chrono>
#include <omp.h>
#include <math.h>
#include <String>
#include <algorithm>

using namespace std;
using namespace chrono;

const int MAX_CHAR = 26;

#define SIZE 10
const int n = 4;
int main()
{
    int mat[SIZE][SIZE] = {};
    int temp[n * n];
    cout << "Matricea initiala:" << endl;
    int value1 = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            value1 = rand() % 10;
            mat[i][j] = value1;
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    // SECVENTIAL
    auto start1 = high_resolution_clock::now();
    int k = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            temp[k++] = mat[i][j];
    sort(temp, temp + k);
    k = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = temp[k++];

    cout << "Matricea sortata:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    auto end1 = high_resolution_clock::now();
    cout << "Time elapsed for secvential " << duration_cast<microseconds>(end1 - start1).count() << " microseconds" << endl;

    // PARALEL
    int mat1[SIZE][SIZE] = {};
    cout << "Matricea initiala:" << endl;
    int value = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            value = rand() % 10;
            mat1[i][j] = value;
            cout << mat1[i][j] << " ";
        }
        cout << endl;
    }
    auto start = high_resolution_clock::now();
    omp_set_num_threads(n);
    int threads_num = omp_get_thread_num();
#pragma omp parallel
    {
        int slice = n;
        int start = threads_num * slice;
        int stop = start + slice;
        int h = 0;
        for (int i = start; i < stop; i++)
            for (int j = start; j < stop; j++)
                temp[h++] = mat1[i][j];
        sort(temp, temp + h);
        h = 0;
        for (int i = start; i < stop; i++)
            for (int j = start; j < stop; j++)
                mat1[i][j] = temp[h++];
    }
    cout << "Matricea sortata:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << mat1[i][j] << " ";
        cout << endl;
    }
    auto end = high_resolution_clock::now();
    cout << "Time elapsed for parallel " << duration_cast<microseconds>(end - start).count() << " microseconds" << endl;

    int mat2[SIZE][SIZE] = {};
    cout << "Matricea initiala:" << endl;
    int value2 = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            value2 = rand() % 10;
            mat2[i][j] = value2;
            cout << mat2[i][j] << " ";
        }
        cout << endl;
    }
    auto start2 = high_resolution_clock::now();
    k = 0;
#pragma omp parallel
    {
#pragma omp parallel for
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                temp[k++] = mat2[i][j];
        sort(temp, temp + k);
        k = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat2[i][j] = temp[k++];
    }
    auto end2 = high_resolution_clock::now();
    cout << "Matricea sortata:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << mat1[i][j] << " ";
        cout << endl;
    }
    cout << "Time elapsed for parallel " << duration_cast<microseconds>(end2 - start2).count() << " microseconds" << endl;
    return 0;
}
