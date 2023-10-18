#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Merge Sort
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Heap Sort
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

int main() {
    int n;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];
    int arr_copy[n]; // Copy for Quick Sort

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        arr_copy[i] = arr[i]; // Copy for Quick Sort
    }

    printf("Original Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Merge Sort
    clock_t start = clock();
    mergeSort(arr, 0, n - 1);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nMerge Sort:\nSorted Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nTime taken: %f seconds\n", time_taken);
    printf("Time Complexity: O(n*log(n)) in all cases (best, average, worst)\n");

    // Quick Sort
    start = clock();
    quickSort(arr_copy, 0, n - 1);
    end = clock();
    double time_taken_quick = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nQuick Sort:\nSorted Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr_copy[i]);
    }
    printf("\nTime taken: %f seconds\n", time_taken_quick);
    printf("Time Complexity: Best-case O(n*log(n)), Average-case O(n*log(n)), Worst-case O(n^2)\n");

    // Heap Sort
    start = clock();
    heapSort(arr, n);
    end = clock();
    double time_taken_heap = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nHeap Sort:\nSorted Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nTime taken: %f seconds\n", time_taken_heap);
    printf("Time Complexity: Best-case O(n*log(n)), Average-case O(n*log(n)), Worst-case O(n*log(n))\n");

    // Compare and determine which sorting algorithm is best
    if (time_taken < time_taken_quick && time_taken < time_taken_heap) {
        printf("\nMerge Sort is the fastest sorting algorithm for this input data.\n");
    } else if (time_taken_quick < time_taken && time_taken_quick < time_taken_heap) {
        printf("\nQuick Sort is the fastest sorting algorithm for this input data.\n");
    } else {
        printf("\nHeap Sort is the fastest sorting algorithm for this input data.\n");
    }

    return 0;
}
