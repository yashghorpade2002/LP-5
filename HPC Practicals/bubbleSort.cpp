#include <iostream>
#include <omp.h>

using namespace std;

void bubbleSort(int arr[], int n)
{

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void pBubbleSort(int arr[], int n)
{

    for (int i = 0; i < n; ++i)
    {
#pragma omp for
        for (int j = 1; j < n; j += 2)
        {
            if (arr[j] < arr[j - 1])
            {
                swap(arr[j], arr[j - 1]);
            }
        }

#pragma omp barrier

#pragma omp for
        for (int j = 2; j < n; j += 2)
        {
            if (arr[j] < arr[j - 1])
            {
                swap(arr[j], arr[j - 1]);
            }
        }
    }
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

int main()
{
    // Set up variables
    int n = 10;
    int arr[10];
    int brr[10];
    double start_time, end_time;

    // Create an array with numbers starting from n to 1
    for (int i = 0, j = n; i < n; i++, j--)
        arr[i] = j;

    // Sequential time
    start_time = omp_get_wtime();
    bubbleSort(arr, n);
    end_time = omp_get_wtime();
    cout << "Sequential Bubble Sort took : " << end_time - start_time << " seconds.\n";
    printArray(arr, n);

    // Reset the array
    for (int i = 0, j = n; i < n; i++, j--)
        arr[i] = j;

    // Parallel time
    start_time = omp_get_wtime();
    pBubbleSort(arr, n);
    end_time = omp_get_wtime();
    cout << "Parallel Bubble Sort took : " << end_time - start_time << " seconds.\n";
    printArray(arr, n);

    return 0;
}