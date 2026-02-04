#include <stdio.h>

int main(){

    return 0;
}

struct Student
{
    int id;
    char name[50];
    int age;
};

void menu(){

    printf("\n---- MENU ----\n");
    printf("*******************");
    printf("First you must choose 1!!\n");
    printf("*******************");
    printf("1. Add student\n");
    printf("2. Print students\n");
    printf("3. Find student by ID\n");
    printf("4. Count of student\n");
    printf("0. End\n\n");

}
