#include <stdio.h>

struct Student {
    int id;
    char name[50];
    int age;
};

void menu();
int readChoice();
void addStudent(struct Student arr[], int *count);
void printStudent(struct Student arr[], int *count);
int findStudent(struct Student arr[], int count, int id);
int countStudent(struct Student arr[], int *count);

int main(){

    struct Student students[50];
    int count = 0;
    int choice;

    while(1){

        menu();
        int choice = readChoice();
        int id;

        switch (choice){

            case 1:
                addStudent(students, &count);
                break;
            
            case 2: 
                printStudent(students, &count);
                break;

            case 3: 
                printf("Please enter ID: ");
                scanf("%d", &id);
                printf("\n");

                int find = findStudent(students, count, id);
                
                if(find == -1){
                    printf("Can't find student!");
                }else{
                    printf("ID: %d\n", students[find].id);
                    printf("Meno: %s\n", students[find].name);
                    printf("Vek: %d\n", students[find].age);
                }
                break;

                case 4:
                    countStudent(students, &count);
                    break;
        }

    }

    

    return 0;
}

void menu(){

    printf("\n---- MENU ----\n");
    printf("*******************\n");
    printf("First you must choose 1!!\n");
    printf("*******************\n");
    printf("1. Add student\n");
    printf("2. Print students\n");
    printf("3. Find student by ID\n");
    printf("4. Count of student\n");
    printf("0. End\n\n");

}

int readChoice(){

    int choice = 0;

    printf("Your choice: ");
    scanf("%d", &choice);
    printf("\n");

    return choice;

}


void addStudent(struct Student arr[], int *count){

    printf("Enter ID: ");
    scanf("%d", &arr[*count].id);

    printf("Enter name: ");
    scanf("%s", arr[*count].name);

    printf("Enter age: ");
    scanf("%d", &arr[*count].age);

    (*count)++;

}

void printStudent(struct Student arr[], int *count){
    
    for(int i = 0; i < *count; i++){
        printf("Student %d\n", i + 1);
        printf("ID: %d\n", arr[i].id);
        printf("Name: %s\n", arr[i].name);
        printf("Age: %d\n", arr[i].age);
    }

}

int findStudent(struct Student arr[], int count, int id){

    for(int i = 0; i < count; i++){
        if(arr[i].id == id){
            return i;
        }
    }

    return -1;
}

int countStudent(struct Student arr[], int *count){

    int sum = 0;

    for(int i = 0; i < *count; i++){
        sum++;
    }

    printf("Count of students is: %d", sum);

    return sum;
}

