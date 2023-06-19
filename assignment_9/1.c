#include <stdio.h>

void merge(int l, int m, int r, int* arr)
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

void mergesort(int l, int r, int* arr)
{
    if(l >= r) 
        return;
    int m = (l + r)/2;
    mergesort(l, m, arr);
    mergesort(m + 1, r, arr);
    merge(l, m, r, arr);
}

void run()
{
    int n;
    printf("Enter the array size.\n");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the array elements\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    mergesort(0, n-1, arr);
    for(int i = 1; i < n; i++)
        if(arr[i] == arr[i-1])
            printf("%d\n", arr[i]);    
}

int main()
{
    run();
    return 0;
}