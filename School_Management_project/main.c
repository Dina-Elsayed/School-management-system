#include <stdio.h>
#include <stdlib.h>
#include"SCM.h"
#include<String.h>
#include"main_menu.h"
int main()
{
    int gradechoice;
    St_list grade1;
    St_list grade2;
    St_list grade3;
    printf("Welcome in our program\n");
    do
    {
        printf("===================\n");
        printf("Please,Enter number of your choice\n");
        printf("1-Grade1\n2-Grade2\n3-Grade3\n4-Exit\n");
        printf("===================\n");
        scanf("%d",&gradechoice);
        switch(gradechoice)
        {
            case GRADE1:
                printf("\nWelcome in Grade1\n");
                main_menu(&grade1);
                break;
            case GRADE2:
                printf("\nWelcome in Grade2\n");
                main_menu(&grade2);
                break;
            case GRADE3:
                printf("\nWelcome in Grade3\n");
                main_menu(&grade3);
                break;
            case Exit:
                printf("\nBye\n");
                break;
            default:
                printf("\nWrong Choice\n");
        }
    }while(gradechoice!=Exit);

    return 0;
}
