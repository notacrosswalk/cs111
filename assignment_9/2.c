#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void merge(int l, int m, int r, int* arr, int* count)
{
    int left = l;
    int right = m + 1;
    int size = r - l + 1;
    int temp[size];
    int i = 0;
    while(left <= m && right <= r)
    {
        if(arr[left] <= arr[right])
        {
            temp[i++] = arr[left++]; 
        }
        else
        {   
            temp[i++] = arr[right++];
            *count += 1;
        }
    }
    while(left <= m)
    {
        temp[i++] = arr[left++];
    }
    while(right <= r)
    {
        temp[i++] = arr[right++];
    }
    for(int j = l; j <= r; j++)
    {
        arr[j] = temp[j - l];
    }
}

void mergesort(int l, int r, int* arr, int *count)
{
    if(l >= r) 
        return;
    int m = (l + r)/2;
    mergesort(l, m, arr, count);
    mergesort(m + 1, r, arr, count);
    merge(l, m, r, arr, count);
}

void selectionsort(int *arr, int n, int* count)
{
    for(int i = 0; i < n - 1; i++)
    {
        int min = i;
        for(int j = i + 1; j < n; j++)
        {
            if(arr[j] < arr[min])
            {
                min = j;
            }
        }
        if(min != i)
        {
            swap(&arr[i], &arr[min]);
            *count += 1;
        }
    }
}

void bubblesort(int *arr, int n, int* count)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 1; j < n - i; j++)
        {
            if(arr[j] < arr[j - 1])
            {
                swap(&arr[j], &arr[j-1]);
                *count += 1;
            }
        }
    }
}

void insertionsort(int *arr, int n, int *count)
{
    for(int i = 0; i < n; i++)
    {
        int j = i;
        while(j > 0 && arr[j] < arr[j - 1])
        {
            swap(&arr[j], &arr[j-1]);
            *count += 1;
            j--;
        }
    }
}

int partition(int *arr, int l, int r, int* count)
{
    int pivot = arr[r];
    int i = l;
    int j = r;
    while(i < j)
    {
        while(arr[i] <= pivot && i <= r - 1)
        {
            i++;
        }
        while(arr[j] > pivot && j >= l + 1)
        {
            j--; 
        }
        if(i < j) 
        {
            swap(&arr[i], &arr[j]);
            *count += 1;
        }
    }
    swap(&arr[l], &arr[j]);
    *count += 1;
    return j;
}

void quicksort(int *arr, int l, int r, int *count)
{
    if(l >= r) return;
    int loc = partition(arr, l, r, count);
    quicksort(arr, l, loc - 1, count);
    quicksort(arr, loc + 1, r, count);
}

int main()
{
    int counts[5];
    int arr0[] = {10, 2, 3, 1, 56, 48, 24, 79, 11, 90, 35, 23, 36, 78};
    int arr1[] = {10, 2, 3, 1, 56, 48, 24, 79, 11, 90, 35, 23, 36, 78};
    int arr2[] = {10, 2, 3, 1, 56, 48, 24, 79, 11, 90, 35, 23, 36, 78};
    int arr3[] = {10, 2, 3, 1, 56, 48, 24, 79, 11, 90, 35, 23, 36, 78};
    int arr4[] = {10, 2, 3, 1, 56, 48, 24, 79, 11, 90, 35, 23, 36, 78};
    int size = sizeof(arr0)/sizeof(int);
    bubblesort(arr0, size, counts);
    selectionsort(arr1, size, counts+1);
    insertionsort(arr2, size, counts+2);
    mergesort(0, size - 1, arr3, counts+3);
    quicksort(arr4, 0, size-1, counts+4);

    // for(int i = 0; i < 5; i++)
    //     printf("%d\n", counts[i]);

    int min = 0;
    for(int i = 1; i < 5; i++)
    {
        if(counts[i] < counts[min])
        {
            min = i;
        }
    }
    switch(min)
    {
        case 0:
            printf("Bubble sort\n");
            break;
        case 1:
            printf("Selection sort\n");
            break;
        case 2:
            printf("Insertion sort\n");
            break;
        case 3:
            printf("Merge sort\n");
            break;
        case 4:
            printf("Quick sort\n");
            break;
    }
    return 0;
}