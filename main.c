#pragma clang diagnostic push
#pragma ide diagnostic ignored "DanglingPointer"
#pragma ide diagnostic ignored "misc-no-recursion"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int *array, int n);
void swap(int *a, int *b);
void quickSort(int low, int high, int *list);
int partition(int low, int high, int *list);
int isSorted(int *vals, int low, int high);
void mergeSort(int *list, int low, int high);
void merge(int *list, int low, int mid, int high);
void selectionSort(int *list, int n);
void insertionSort(int *list, int n);

int main(void) {

    int user = 1;
    int max = 10000;
    int n = 10;
    srand(time(NULL));
    int* list = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) list[i] = rand() % max;

    printf("Hello, Please pick an option:\n");

    while(user != 0) {

        printf("1: Generate an array of random values to sort\n");
        printf("2: Use Quick Sort to sort\n");
        printf("3: Use Merge Sort\n");
        printf("4: Use Bubble Sort\n");
        printf("5: Use Insertion Sort\n");
        printf("6: Use Selection Sort\n");
        printf("7: Print Array\n");
        printf("0: Quit\n");

        scanf("%d", &user);
        
        switch(user){
            case 1: {
                printf("Enter the size of the array\n");
                scanf("%d", &n);
                printf("Enter the maximum value possible\n");
                scanf("%d", &max);
                list = realloc(list, sizeof(int) * n);
                for(int i = 0; i < n; i++)
                    list[i] = rand() % max;
                break;
            }
            case 2: {
                if(n > 30){
                    quickSort(0, n - 1, list);
                    break;
                } else {
                    bubbleSort(list, n);
                }

            }
            case 3: {
                mergeSort(list, 0, n - 1);
                break;
            }
            case 4: {
                bubbleSort(list, n);
                break;
            }
            case 5: {
                insertionSort(list, n);
                break;
            }
            case 6: {
                selectionSort(list, n);
                break;
            }
            case 7: {
                for(int i = 0; i < n; i++) printf("%d\n", list[i]);
                break;
            }
            case 0:{
                printf("Goodbye!\n");
                user = 0;
                free(list);
                break;
            }
            default:
                printf("Invalid option\n");
                break;
        }


    }

    free(list);
    return 0;
}

void selectionSort(int *list, int n){

    int low;

    for(int i = 0; i < n; i++){

        low = i;

        for(int j = i + 1; j < n; j++){

            if(list[j] < list[low])
                low = j;
        }

        swap(&list[i], &list[low]);
    }
}

void insertionSort(int *list, int n){

    int j;

    for(int i = 1; i < n; i++){

        j = i;

        while(j > 0 && list[j] < list[j -1]){
            swap(&list[j], &list[j - 1]);
            j--;
        }
    }
}

int isSorted(int *vals, int low, int high){
    for(int i = low; i < high; i++){
        if(vals[i] > vals[i+1])
            return 0;
    }
      return 1;
}

void quickSort(int low, int high, int *list){

    if(isSorted(list, low, high)) return;

    int index = partition(low, high, list);

    quickSort(low, index - 1, list);
    quickSort(index + 1, high, list);

}

int partition(int low, int high, int *list){

    int i, bottom;

    i = low + rand()%(high - low + 1); //finds a random element in the array to use as the partition element
    swap(&list[i], &list[low]);// swaps with the beginning element

    bottom = low; //stores index of partition element and increases the low index
    low++;

    while(low <= high){//run through the array till it finds values to big or small to be on that side and then swaps
        //them accordingly

        while(low <= high && list[low] <= list[bottom]) low++;

        while(high >= low && list[high] > list[bottom]) high--;

        if(low < high) swap(&list[low], &list[high]);
    }
    swap(&list[bottom], &list[high]);//swaps the partition element back

    return high;//returns the partition index
}

void merge(int *list, int low, int mid, int high){

    int length = high - low + 1;

    int *tmp = (int*) calloc(length, sizeof(int));//tmp to store sorted values

    int count1 = low;//counters for list
    int count2 = mid;

    int mc = 0;//merge counter

    while((count1 < mid) || (count2 <= high)){//copies vals from list one and then list 2

        if(count2 > high || (count1 < mid && list[count1] < list[count2])){

            tmp[mc] = list[count1];
            count1++;
            mc++;

        } else {

            tmp[mc] = list[count2];
            count2++;
            mc++;

        }

    }

    // Copy back all of our values into the original array.
    for (int i= low; i<= high; i++)
        list[i] = tmp[i - low];

    free(tmp);//free tmp now that it's no longer needed
}

void mergeSort(int *list, int low, int high){

    int mid;

    if(low < high){
        mid = (high+low)/2;

        mergeSort(list, low, mid);//call on left half of array

        mergeSort(list, mid + 1, high);//call on right half

        merge(list, low, mid + 1, high);//recombine and sort
    }

}


void bubbleSort(int *array, int n){

    for(int i = n -1; i > 0; i--){
        for(int j = 0; j < i; j++){
            if(array[j] > array[j + 1])
                swap(&array[j], &array[j + 1]);
        }
    }

}

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
#pragma clang diagnostic pop