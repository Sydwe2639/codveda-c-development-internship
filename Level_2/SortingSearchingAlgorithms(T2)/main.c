/*
 * Level 2 (Intermediate) - Task 2: Sorting and Searching Algorithms
 *
 * Description: Implements Bubble Sort, Quick Sort, Linear Search, and
 * Binary Search, and reports the time taken by each so their performance
 * can be compared.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ---------- Sorting Algorithms ---------- */

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                    //Sworp
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
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

/* ---------- Searching Algorithms ---------- */

int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) return i;
    }
    return -1;
}

int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) return mid;
        if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

/* ---------- Helpers ---------- */

void copyArray(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

void printArray(int arr[], int n) {
    int limit = n < 20 ? n : 20;
    for (int i = 0; i < limit; i++) printf("%d ", arr[i]);
    if (n > 20) printf("...");
    printf("\n");
}

int main(void) {
    int n;
    printf("===== Sorting and Searching Algorithms =====\n");
    printf("Enter the number of elements to generate: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Array size must be positive.\n");
        return 1;
    }

    int *original = malloc(n * sizeof(int));
    int *bubbleArr = malloc(n * sizeof(int));
    int *quickArr  = malloc(n * sizeof(int));

    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) original[i] = rand() % 10000;

    copyArray(original, bubbleArr, n);
    copyArray(original, quickArr, n);

    printf("\nOriginal array (first 20 shown): ");
    printArray(original, n);

    // Bubble Sort timing
    clock_t start = clock();
    bubbleSort(bubbleArr, n);
    clock_t end = clock();
    double bubbleTime = (double)(end - start) / CLOCKS_PER_SEC;

    // Quick Sort timing
    start = clock();
    quickSort(quickArr, 0, n - 1);
    end = clock();
    double quickTime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nBubble sorted (first 20 shown): ");
    printArray(bubbleArr, n);
    printf("Bubble Sort time:  %.6f seconds (O(n^2))\n", bubbleTime);

    printf("\nQuick sorted (first 20 shown): ");
    printArray(quickArr, n);
    printf("Quick Sort time:   %.6f seconds (O(n log n) average)\n", quickTime);

    //Searching demo
    int key;
    printf("\nEnter a value to search for: ");
    scanf("%d", &key);

    start = clock();
    int linIdx = linearSearch(original, n, key);
    end = clock();
    double linTime = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    int binIdx = binarySearch(quickArr, n, key); // binary search needs sorted array
    end = clock();
    double binTime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nLinear Search (on unsorted array): %s (index in original array: %d) - %.6f seconds\n",
           linIdx != -1 ? "FOUND" : "NOT FOUND", linIdx, linTime);
    printf("Binary Search (on sorted array):    %s (index in sorted array: %d) - %.6f seconds\n",
           binIdx != -1 ? "FOUND" : "NOT FOUND", binIdx, binTime);

    free(original);
    free(bubbleArr);
    free(quickArr);
    return 0;
}
