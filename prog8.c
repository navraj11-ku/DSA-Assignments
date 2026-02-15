#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int arr[], int n, int *comp, int *swap) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            (*comp)++;
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                (*swap)++;
            }
        }
    }
}

void selectionSort(int arr[], int n, int *comp, int *swap) {
    for(int i = 0; i < n - 1; i++) {
        int min = i;
        for(int j = i + 1; j < n; j++) {
            (*comp)++;
            if(arr[j] < arr[min]) {
                min = j;
            }
        }
        if(min != i) {
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
            (*swap)++;
        }
    }
}

void insertionSort(int arr[], int n, int *comp, int *swap) {
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while(j >= 0) {
            (*comp)++;
            if(arr[j] > key) {
                arr[j + 1] = arr[j];
                (*swap)++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

int merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];
    for(i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for(j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0; j = 0; k = left;
    int comp = 0;

    while(i < n1 && j < n2) {
        comp++;
        if(L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while(i < n1)
        arr[k++] = L[i++];
    while(j < n2)
        arr[k++] = R[j++];

    return comp;
}

int mergeSort(int arr[], int left, int right) {
    int comp = 0;
    if(left < right) {
        int mid = (left + right) / 2;
        comp += mergeSort(arr, left, mid);
        comp += mergeSort(arr, mid + 1, right);
        comp += merge(arr, left, mid, right);
    }
    return comp;
}

int main() {
    int N, choice;
    printf("Enter value of N: ");
    scanf("%d", &N);

    int arr[N];
    srand(time(0));

    for(int i = 0; i < N; i++) {
        arr[i] = rand() % 1000 + 1;
    }

    printf("\nBefore Sorting:\n");
    for(int i = 0; i < N; i++)
        printf("%d ", arr[i]);

    printf("\n\nChoose Sorting Algorithm:\n");
    printf("1. Bubble Sort\n");
    printf("2. Selection Sort\n");
    printf("3. Insertion Sort\n");
    printf("4. Merge Sort\n");
    printf("Enter choice (1-4): ");
    scanf("%d", &choice);

    int comp = 0, swap = 0;

    if(choice == 1)
        bubbleSort(arr, N, &comp, &swap);
    else if(choice == 2)
        selectionSort(arr, N, &comp, &swap);
    else if(choice == 3)
        insertionSort(arr, N, &comp, &swap);
    else if(choice == 4)
        comp = mergeSort(arr, 0, N - 1);
    else {
        printf("Invalid choice\n");
        return 0;
    }

    printf("\nAfter Sorting:\n");
    for(int i = 0; i < N; i++)
        printf("%d ", arr[i]);

    printf("\n\nTotal Comparisons: %d\n", comp);
    if(choice == 4)
        printf("Total Swaps: Not Applicable\n");
    else
        printf("Total Swaps: %d\n", swap);

    return 0;
}
