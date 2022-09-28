#include <stdio.h>
#include <stdlib.h>
#include "SCM.h"
#include <stdbool.h>
#include<string.h>
#include"main_menu.h"
void main_menu(St_list*student)
{
    int choice, id, day, month,year, phoneno;
    double CS,AI,OS;
    char name[SIZE];
    char address[SIZE];
    create_list(student);
    do
    {
        printf("\n=============================\n");
        printf("Please choose from following:\n");
        printf("1-Insert data\n2-Print list\n3-Delete from list\n4-Search in list\n5-Edit\n6-Update score\n7-STUDENT_RANK\n8-Exit\n");
        printf("\n=============================\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case INSERT:
             printf("Enter ID\n");
             scanf("%d",&id);
             printf("Enter name:\n ");
             fflush(stdin);
            gets(name);
            printf("Enter address: \n");
            fflush(stdin);
            gets(address);
            printf("Enter Date of Birth: \n");
            scanf("%d/%d/%d",&day,&month,&year);
            printf("Enter phone Number: \n");
            scanf("%d",&phoneno);
            printf("Enter CS Grade\n");
            scanf("%lf",&CS);
            printf("Enter AI Grade\n");
            scanf("%lf",&AI);
            printf("Enter OS Grade\n");
            scanf("%lf",&OS);
            status y = New_Student(student,id,day,month,year,phoneno,name,address,CS,AI,OS);
            if(y==success){
            printf("%d is inserted\n",id);
            }
            break;
        case PRINT:
            printf("Student sorted Alphabetically\n");
            print_list(student);
            break;
        case DELETE:
            printf("Please Enter ID to delete\n");
            scanf("%d",&id);
            status x = Delet_Student(student,id);
            if(x==success){
            printf("%d is deleted\n",id);
            }
            break;
            case SEARCH:
            printf("Please Enter ID to Search\n");
            scanf("%d",&id);
            Student_Node*result =search_Student(student,id);
            if(result==NULL) printf("Not Found\n");
            else printf("Found\n");
            break;
        case EDIT:
            printf("Please,Enter ID to Edit\n");
            scanf("%d",&id);
            Student_Edit(student,id);
            break;
        case UPDATE_SCORE:
            STUDENT_SCORE(student);
            break;
        case STUDENT_RANK:
            printf("Student sorted according to CS grade\n");
            Student_Rank(student);
            break;
        case EXIT:
            printf("\nBye\n");
            break;
        default:
            printf("wrong choice\n");
        }
    }while(choice !=EXIT);
}
