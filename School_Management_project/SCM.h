#ifndef SCM_H_INCLUDED
#define SCM_H_INCLUDED

#include <stdbool.h>

#define ADDRESS 1
#define DATE 2
#define PHONE_NO 3
#define cs 1
#define ai 2
#define os 3
#define SIZE 40


typedef struct Data
{

    int ID;
    char name[SIZE];
    int day;
    int month;
    int year;
    char address[SIZE];
    int phoneno;

}Data;
typedef struct Subject_Score
{
    double cs_score;
    double AI_score;
    double OS_score;
}Subject_Score;

typedef struct Student_Node
{
    Data*data;
    Subject_Score*score;
    struct Student_Node*pNext;
    struct Student_Node*pPrev;
    struct Student_Node*pleft;
    struct Student_Node*pright;
}Student_Node;

typedef struct St_list
{
    Student_Node*pHead;
    Student_Node*pTail;
    Student_Node*score_Head;
    Student_Node*score_Tail;
    int list_size;
}St_list;

typedef enum
{
    fail,success
}status;


status sorted(St_list*st,int copy_ID);
void main_menu(St_list*st);
void create_list(St_list*st);
status New_Student(St_list*st,int copy_ID,int copy_day,int copy_month,int copy_year,int phoneno,char*copy_name,char*copy_address,double copy_CS,double copy_AI,double copy_OS);
void print_list(St_list*st);
status Delet_Student(St_list*st,int copy_ID);
Student_Node*search_Student(St_list*st,int copy_ID);
status Student_Edit(St_list*st,int copy_ID);
status STUDENT_SCORE(St_list*st);
void Student_Rank(St_list*st);

#endif // SCM_H_INCLUDED
