#include <iostream>
#include <omp.h>

using namespace std;

int min(int arr[], int n){

    int minval = arr[0];
    #pragma omp parallel for reduction(min : minval)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < minval)
            minval = arr[i];
    }
    return minval;
}


int max(int arr[], int n){

    int maxval = arr[0];
    #pragma omp parallel for reduction(max : maxval)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > maxval)
            maxval = arr[i];  
    }

    return maxval;
}


int sum(int arr[], int n){

    int sum = 0;

    #pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum;
}


double avg(int arr[], int n){
    return sum(arr, n) / n;
}


int main() {

    int n = 5;
    int arr[] = {1, 2, 3, 4, 5};

    cout << "Max value is:  " << max(arr, n) << endl;
    cout << "Min Value isL " << min(arr, n) << endl;
    cout << "Sum Value is: " << sum(arr, n) << endl;
    cout << "Average Value is: " << avg(arr, n) << endl;


    return 0;
}