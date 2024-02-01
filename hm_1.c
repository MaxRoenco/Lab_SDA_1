#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_arr(int* arr, int n){
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void delete(int* arr, int* n){
    for(int i = 0; i < *n - 1; i++){
        arr[i] = arr[i + 1];
    }
    (*n)--;
}

void bubble_sort(int* arr, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - i; j++){
            if(arr[j] < arr[j + 1]){
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void selection_sort(int* arr, int n){
    for(int i = 0; i < n; i++){
    int min = arr[i];
    int min_index = i;
        for(int j = i; j < n; j++){
            if(arr[j] <= min){
                min = arr[j];
                min_index = j;
            }
        }
        swap(&arr[i], &arr[min_index]);
    }
}

void insertion_sort(int* arr, int n){
    for(int i = 1; i < n; i++){
        int j = i;
        while(j > 0 && (arr[j] < arr[j - 1])){
            swap(&arr[j], &arr[j - 1]);
            j--;
        }
    }
}

int binary_search(int* arr, int n, int number){
    int left = 0;
    int right = n - 1;
    int middle_index;
    int count = 0;
    while(left <= right){
        middle_index = left + (right - left) / 2;
        if(arr[middle_index] > number){
            right = middle_index - 1;
        }
        else if(arr[middle_index] < number){
            left = middle_index + 1;
        } 
        else{
            printf("\nWe found our number! - %d\n", middle_index);
            return middle_index;
        }
    }
    printf("Not found\n");
    return -1;
}

int partition(int* arr, int low, int high){
    int pivot_index = high;
    int j = 0;
    for(int i = 0; i < high; i++){
        if(arr[i] <= arr[pivot_index]){
            swap(&arr[j], &arr[i]);
            j++;
        }
    }
    swap(&arr[j], &arr[pivot_index]);
    return j;
}

void quick_sort_recursive(int* arr, int low, int high) {
    if(low >= high) return;
    int pivot = partition(arr, low, high);

    quick_sort_recursive(arr, low, pivot - 1);
    quick_sort_recursive(arr, pivot + 1, high);
}

void quick_sort(int arr[], int n){
    quick_sort_recursive(arr, 0, n - 1);
}

void merge(int* arr, int n, int left, int middle, int right){
    int left_length = middle - left + 1;
    int right_length = right - middle;

    int arr_left[left_length];
    int arr_right[right_length];

    for(int i = 0; i < left_length; i++){
        arr_left[i] = arr[i + left];
    }

    for(int i = 0; i < right_length; i++){
        arr_right[i] = arr[i + middle + 1];
    }

    for(int i = 0, j = 0, k = left; k <= right; k++){
        if((i < left_length) && (j >= right_length || arr_left[i] < arr_right[j])){
            arr[k] = arr_left[i];
            i++;
        }
        else{
            arr[k] = arr_right[j];
            j++;
        }
    }
}

void merge_recursion(int* arr, int n, int left, int right){
    if(left >= right) return;
    int middle = (left + right)/2;

    merge_recursion(arr, n, left, middle);
    merge_recursion(arr, n, middle + 1, right);

    merge(arr, n, left, middle, right);
}

void merge_sort(int* arr, int n){
    merge_recursion(arr, n, 0, n - 1);
}

void check_repeated_number(int* arr, int n, int number){
    int count = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] == number){
            printf("Number %d, index %d\n", number, i);
            count++;
        }
    }
    printf("In total %d numbers\n", count);
}

void printMenu() {
    printf("+--------------------------------------+\n");
    printf("|               Menu                   |\n");
    printf("+--------------------------------------+\n");
    printf("| 0 - Exit                             |\n");
    printf("| 1 - Delete first element-> Merge sort|\n");
    printf("| 2 - Insertion sort                   |\n");
    printf("| 3 - Selection Sort                   |\n");
    printf("| 4 - Bubble Sort in descending form   |\n");
    printf("| 5 - Quick Sort                       |\n");
    printf("| 6 - Find number using Binary search  |\n");
    printf("| 7 - Print array                      |\n");
    printf("+--------------------------------------+\n");
}

int main() {
    srand(time(NULL));
    int k;
    int n;
    int number;
    int* arr;
    start:
    printf("+--------------------------------------+\n");
    printf("|               Menu                   |\n");
    printf("+--------------------------------------+\n");
    printf("| 0 - Exit                             |\n");
    printf("| 1 - Input numbers in array (keyboard)|\n");
    printf("| 2 - Input numbers in array randomly  |\n");
    printf("+--------------------------------------+\n");
    scanf("%d", &k);
    switch(k){
        case 0:
            goto start;
            break;
        case 1:
            printf("Input number of digits:");
            scanf("%d", &n);
            arr = (int*)malloc(sizeof(int) * n);
            for(int i = 0; i < n; i++){
                scanf("%d", &arr[i]);
            }
            print_arr(arr, n);
            break;
        case 2:
            printf("Input number of digits:");
            scanf("%d", &n);
            arr = (int*)malloc(sizeof(int) * n);
            for(int i = 0; i < n; i++){
            arr[i] = rand() % 200 - 100;
            }
            print_arr(arr, n);
            break;
    }

    printMenu();

    scanf("%d", &k);
    switch(k){
    case 0:
        return 1;
    case 1:
        print_arr(arr, n);
        printf("\n\n");
        number = arr[0];
        check_repeated_number(arr, n, number);
        delete(arr, &n);
        print_arr(arr, n);
        printf("\n\n");
        merge_sort(arr, n);
        print_arr(arr, n);
        break;
    case 2:
        insertion_sort(arr, n);
        print_arr(arr, n);
        break;
    case 3:
        selection_sort(arr, n);
        print_arr(arr, n);
        break;
    case 4:
        bubble_sort(arr, n);
        print_arr(arr, n);
        break;
    case 5:
        quick_sort(arr, n);
        print_arr(arr, n);
        break;
    case 6:
        merge_sort(arr, n);
        print_arr(arr, n);
        printf("Input number:");
        scanf("%d", &number);
        binary_search(arr, n, number);
        break;
    case 7:
        print_arr(arr, n);
        break;
    }
    free(arr);
    goto start;
    return 0;
}
