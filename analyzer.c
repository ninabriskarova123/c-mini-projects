#include <stdio.h>

int getNumber(int arr[]);
int sumNumber(int arr[], int n);
int maxNumber(int arr[], int n);
int evenNumber(int arr[], int n);

int main(){

    int n[100];

    int number = getNumber(n);
    int sum = sumNumber(n, number);
    int max = maxNumber(n, number);
    int even = evenNumber(n, number);

    return 0;
}

int getNumber(int arr[]){

    int n = 0;

    while (1) {
        printf("Zadaj cislo (-1 pre koniec): ");
        scanf("%d", &arr[n]);

        if (arr[n] == -1) {
            break;
        }

        if (n >= 99) {
            break;
        }

        n++;
    }

    return n;
}

int sumNumber(int arr[], int n){

    int sum = 0;

    for(int i = 0; i < n; i++){
        sum += arr[i];
    }

    printf("Sum of your number is: %d\n", sum);

    return sum;

}

int maxNumber(int arr[], int n){

    int max = 0;

    for(int i = 0; i < n; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }

    printf("Max. number is: %d\n", max);

    return max;
}

int evenNumber(int arr[], int n){
    
    int even = 0;

    for(int i = 0; i < n; i++){
        if(arr[i] % 2 == 0){
            even++;
        }
    }

    printf("Count of even numbers is: %d\n", even);

    return even;
}