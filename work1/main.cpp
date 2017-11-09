#include <iostream>
#include <random>
#include <ctime>

using namespace std;

#define N 10000

void printArr(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void swap(int *arr, int i, int j) {
    if (i == j) return;

    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// SELECTION_SORT
int min_index(int *arr, int n, int begin) {
    int minIndex = begin;
    for (int i = begin + 1; i < n; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

int *selection_sort(int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        swap(arr, min_index(arr, n, i), i);
    }
    return arr;
}


// BUBBLE_SORT
int *bubble_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr, j, j + 1);
            }
        }
    }
    return arr;
}


// INSERT_SORT
int *insert_sort(int *arr, int n) {
    for (int i = 1; i < n; ++i) {
        int num = arr[i];
        int j = i - 1;

        for (; j >= 0 && arr[j] > num; --j) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = num;
    }
    return arr;
}


// QUICK_SORT
int partition(int *arr, int left, int right, int pivotIndex) {
    int pivot = arr[pivotIndex];
    swap(arr, pivotIndex, right);

    int storeIndex = left;
    for (int i = left; i < right; ++i) {
        if (arr[i] <= pivot) {
            swap(arr, storeIndex, i);
            storeIndex++;
        }
    }
    swap(arr, right, storeIndex);

    return storeIndex;
}

int *quick_sort_recursive(int *arr, int left, int right) {
    if (left < right) {
        int pivotNewIndex = partition(arr, left, right, left);
        quick_sort_recursive(arr, left, pivotNewIndex - 1);
        quick_sort_recursive(arr, pivotNewIndex + 1, right);
    }
    return arr;
}

int *quick_sort(int *arr, int len) {
    return quick_sort_recursive(arr, 0, len - 1);
}


// MERGE_SORT
int *merge_sort_recursive(int *arr, int *reg, int start, int end) {
    if (start >= end) return nullptr;
    int len = end - start;
    int mid = start + len / 2;

    int start1 = start;
    int end1 = mid;
    int start2 = mid + 1;
    int end2 = end;

    merge_sort_recursive(arr, reg, start1, end1);
    merge_sort_recursive(arr, reg, start2, end2);

    int k = start;

    while (start1 <= end1 && start2 <= end2) {
        reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
    }

    while (start1 <= end1) {
        reg[k++] = arr[start1++];
    }
    while (start2 <= end2) {
        reg[k++] = arr[start2++];
    }

    for (k = start; k <= end; k++) {
        arr[k] = reg[k];
    }
    return arr;
}

int *merge_sort(int *arr, const int len) {
    int reg[len];
    return merge_sort_recursive(arr, reg, 0, len - 1);
}


const int QUICK_SORT = 0;
const int MERGE_SORT = 1;
const int INSERT_SORT = 2;
const int SELECTION_SORT = 3;
const int BUBBLE_SORT = 4;

int *do_sort(int type, int *arr, int n) {
    switch (type) {
        case SELECTION_SORT:
            return selection_sort(arr, n);
        case BUBBLE_SORT:
            return bubble_sort(arr, n);
        case INSERT_SORT:
            return insert_sort(arr, n);
        case MERGE_SORT:
            return merge_sort(arr, n);
        case QUICK_SORT:
            return quick_sort(arr, n);
        default:
            return nullptr;
    }
}

string print_type(int type) {
    switch (type) {
        case SELECTION_SORT:
            return "Selection sort";
        case BUBBLE_SORT:
            return "Bubble sort";
        case INSERT_SORT:
            return "Insert sort";
        case MERGE_SORT:
            return "Merge sort";
        case QUICK_SORT:
            return "Quick sort";
        default:
            return "";
    }
}


int main() {
    srand((unsigned int) clock());

    int *arr = new int[N];

    for (int i = QUICK_SORT; i <= BUBBLE_SORT; i++) {
        int cnt = 0;
        const int repeat = 10;

        for (int r = 0; r < repeat; r++) {
            for (int j = 0; j < N; j++) {
                arr[j] = rand() % 1000000 + 1;
            }

            long tic = clock();
            do_sort(i, arr, N);
            long toc = clock();

            cnt += toc - tic;
        }

        cout << print_type(i) << " costs: " << cnt / (double) repeat / 1000 << " ms" << endl << endl;
    }

    return 0;
}