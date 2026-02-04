#include <stdio.h>

void menu(void);
int readChoice();
int readNumber(int arr[]);
void printNumber(int arr[], int n);
int sumNumber(int arr[], int n);
int maxNumber(int arr[], int n);
int evenNumber(int arr[], int n);

int main(){

    int numbers[100];
    int number = 0;
    

    while(1){
        menu();
        int choice = readChoice();
        

        switch (choice){
            case 1: 
                number = readNumber(numbers);
            break;

            case 2:
                printNumber(numbers, number);
            break;

            case 3:
                sumNumber(numbers, number);
                break;
            
            case 4:
                maxNumber(numbers, number);
                break;

            case 5:
                evenNumber(numbers, number);
                break;

            case 0: 
                return 0;

            default:
                printf("Bad choice!");
            }

    
    }


    return 0;
}

void menu(void){

        printf("\n---- MENU ----\n");
        printf("*********\n");
        printf("First you must choose 1!!\n");
        printf("*********\n");
        printf("1 - Zadaj čísla\n");
        printf("2 - Výpis čísla\n");
        printf("3 - Súčet čísla\n");
        printf("4 - Maximum\n");
        printf("5 - Počet párnych čísel\n");
        printf("0 - Koniec\n\n\n");


}

int readChoice(){

    int choice = 0;

    printf("Tvoja voľba: ");
    scanf("%d", &choice);

    return choice;

}

int readNumber(int arr[]){

    int number = 0;

    while(1){
        printf("Zadaj číslo (-1 pre koniec): ");
        scanf("%d", &arr[number]);

        if(arr[number] == -1){
            break;
        }

        if(number >= 99){
            break;
        }

        number++;
    }

    return number;
}

void printNumber(int arr[], int n){

    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }

    printf("\n\n");
   

}

int sumNumber(int arr[], int n){
    int sum = 0;

    for(int i = 0; i < n; i++){
        sum += arr[i];
    }

    printf("Sum of yout numbers is: %d\n\n", sum);


    return sum;
}

int maxNumber(int arr[], int n){
    int max = arr[0];

    for(int i = 0; i < n; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }

    printf("Your max number is: %d\n\n", max);

    return max;
}

int evenNumber(int arr[], int n){
    int even = 0;

    for(int i = 0; i < n; i++){
        if(arr[i] % 2 == 0){
            even++;
        }
    }

    printf("Count of even number is: %d\n\n", even);

    return even;
}

