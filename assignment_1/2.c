#include <stdio.h>

int findingDuplicates(int *arr, int n, int *temp)
{
    int n_duplicates = 0;
    printf("\nThe duplicates are\n");
    int k = 0;
    for(int i = 0; i < n; i++)
    {
        int flag = 0;
        for(int j = 0; j < i; j++)
        {
            if(arr[i] == arr[j])
            {
                flag = 1;
                n_duplicates++;
                printf("%d at index %d\n", arr[i], i);
                break;
            }
        }
        if(!flag) temp[k++] = arr[i];
    }
    if(!n_duplicates) printf("(there seem to be none).\n");
    return n_duplicates;
}

void removeDuplicates(int *arr, int n, int *temp, int n_duplicates, int *narr)
{
    for(int i = 0; i < n - n_duplicates; i++)
        narr[i] = temp[i];
    printf("\nThe array without the duplicates is\n");
    for(int i = 0; i < n - n_duplicates; i++)
        printf("%d ", narr[i]);
    printf("\n");
}

int main()
{
    int n;
    printf("Array size:\n");
    scanf("%d", &n);
    if(!n) return 0;
    int arr[n];
    printf("Enter the array elements:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    //
    int temp[n];
    int n_duplicates = findingDuplicates(arr, n, temp);
    int narr[n-n_duplicates];
    removeDuplicates(arr, n, temp, n_duplicates, narr);
    return 0;
}