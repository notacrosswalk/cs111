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
    printf("Enter the target sum\n");
    int k;
    scanf("%d", &k);
    mergesort(0, n-1, arr);
    int l = 0;
    int r = n - 1;
    while(l < r)
    {
        if(arr[l] + arr[r] > k)
        {
            r -= 1;
        }
        else if(arr[l] + arr[r] < k)
        {
            l += 1;
        }
        else
        {
            printf("Indices: %d and %d\nElements: %d and %d\n", 
                   l, r, arr[l], arr[r]);
            return;
        }
    }
    printf("Not found!\n");
}

int main()
{
    run();
    return 0;
}