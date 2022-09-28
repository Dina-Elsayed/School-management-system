#include <stdio.h>
#include <stdlib.h>
#include"SCM.h"
#include <stdbool.h>
#include<string.h>


void create_list(St_list*st) //initialization list
{
    st->pHead =st->pTail=NULL;
    st->score_Head=st->pTail=NULL;
    st->list_size =0;
}
status New_Student(St_list*st,int copy_ID,int copy_day,int copy_month,int copy_year,int copy_phoneno,char*copy_name,char*copy_address,double copy_CS,double copy_AI,double copy_OS)
{
    //step1:Check ID unique or used before
	Student_Node*search_ = search_Student(st,copy_ID);
    if(search_!=NULL) //ID is used
	{
        printf("\n This ID is used before\n");
		return fail;
	}

	//if unique:
    //step-1:allocate memory for node
   Student_Node*ns = (Student_Node*)malloc(sizeof(Student_Node));
   ns->data= (Data*)malloc(sizeof(Data));
   ns->score=(Subject_Score*)malloc(sizeof(Subject_Score));
   if(ns == NULL)//Heap is full
   {
       printf("NO Available Memory\n");
       return fail;
   }
   //step 2 : initialization node
   //step2.1: initialize Data for this node
   ns->data->ID = copy_ID;
   strcpy(ns->data->name, copy_name);
   ns->data->day= copy_day;
   ns->data->month=copy_month;
   ns->data->year=copy_year;
   strcpy(ns->data->address,copy_address);
   ns->data->phoneno=copy_phoneno;

   //step2.2: initialize Score for this node
   ns->score->cs_score = copy_CS;
   ns->score->AI_score = copy_AI;
   ns->score->OS_score = copy_OS;
   //step2.3: initialize pointers of node
   ns->pNext=ns->pPrev=NULL;
   ns->pleft=ns->pright=NULL;
   //Alphabetically sorted

   if(st->pHead==NULL)//if list is empty
   {
       st->pHead = st->pTail=ns;
   }
   else//Not empty
   {
       //step3: search for correct place
       Student_Node*temp = st->pHead;
       while(temp!=NULL && (strcmp(copy_name,temp->data->name)==1)) //until find name greater than name of new node
       {
           temp = temp->pNext;
       }
       if(temp == st->pHead) //insert @Head
       {
           //step 1 :new node next is old head
           ns->pNext = st->pHead;
           //step 2 : old head prev is new node
          st->pHead->pPrev = ns;
          //step 3 : assign new node as new head
          st->pHead = ns;
       }
       else if(temp==NULL)//@Tail
       {
           //step 1 : assign old tail as new node prev
           ns->pPrev=st->pTail;
           //step 2 : assign new node as old tail`s next
           st->pTail->pNext=ns;
           //step 3 : assign new node as new tail
           st->pTail=ns;
       }
       else//@Middle
       {
           //step1: new node next is  node greater than it
           ns->pNext=temp;
           //step2: new node prev is last smaller node than it
           ns->pPrev = temp->pPrev;
           //step3: next of  last smaller node is temp
           temp->pPrev->pNext=ns;
           //step4: prev of first greater node is temp
           temp->pPrev = ns;
       }
   }


   //CS_score sorted
   if(st->score_Head==NULL)//Empty
   {
       st->score_Head = st->score_Tail = ns;
   }
   else//Not Empty
   {
       //step1: search for correct place
       Student_Node*scoretemp = st->score_Head;
       while(scoretemp!=NULL&&copy_CS > scoretemp->score->cs_score) //until find cs_grade greater than cs_grade of new node
       {
           scoretemp = scoretemp->pright;
       }
       if(scoretemp == st->score_Head) //@Head
       {
           //step 1 :new node right is old head
           ns->pright = st->score_Head;
           //step 2 : old head left is new node
           st->score_Head->pleft = ns;
           //step 3 : assign new node as new head
           st->score_Head = ns;
       }
       else if(scoretemp==NULL) //@Tail
       {
           //step 1 : assign old tail as new node left
           ns->pleft = st->score_Tail;
           //step 2 : assign new node as old tail`s right
           st->score_Tail->pright = ns;
           //step 3 : assign new node as new tail
           st->score_Tail = ns;
       }
       else //@middle
       {
            //step1: new node right is  node greater than it
           ns->pright = scoretemp;
           //step2: new node left is last smaller node than it
           ns->pleft = scoretemp->pleft;
            //step3: right of  last smaller node is temp
           scoretemp->pleft->pright = ns;
           //step4: left of first greater node is temp
           scoretemp->pleft = ns;
       }
   }

   st->list_size++;
   return success;
}


void print_list(St_list*st) //print according to Alphabetical
{
    if(st->pHead==NULL)//Empty
    {
        printf("List is Empty\n");
        return;
    }
    Student_Node*temp = st->pHead;
    int i=0;
    while(temp!= NULL)
    {
        printf("\n====================\n");
        printf("data%d =\nID:%d\nName: %s\nAddress: %s\n",i+1,temp->data->ID,temp->data->name,temp->data->address);
        printf("Date of Birth: %d/%d/%d\nphone Number:%d\n",temp->data->day,temp->data->month,temp->data->year,temp->data->phoneno);
        printf("CS score= %lf\nAI score=%lf\nOS score=%lf\n",temp->score->cs_score,temp->score->AI_score,temp->score->OS_score);
        temp = temp->pNext;
        i++;
    }
}

void Student_Rank(St_list*st) //print according to CS_score
{
    if(st->score_Head==NULL)
    {
        printf("List is Empty\n");
        return;
    }

    Student_Node*scoretemp = st->score_Head;
    int i =0;
    while(scoretemp!=NULL)
    {
         printf("\n====================\n");
         printf("data%d =\nID:%d\nName: %s\n Address: %s\n ",i+1,scoretemp->data->ID,scoretemp->data->name,scoretemp->data->address);
         printf("Date of Birth: %d/%d/%d\n phone Number:%d\n",scoretemp->data->day,scoretemp->data->month,scoretemp->data->year,scoretemp->data->phoneno);
         printf("CS score= %lf\nAI score=%lf\nOS score=%lf\n",scoretemp->score->cs_score,scoretemp->score->AI_score,scoretemp->score->OS_score);
          printf("\n====================\n");
         scoretemp=scoretemp->pright;
         i++;
    }
}

Student_Node*search_Student(St_list*st,int copy_ID)
{
    Student_Node*temp = st->pHead;
    while(temp!= NULL&&copy_ID!=temp->data->ID)
    {
        temp = temp->pNext;
    }
    return temp;
}

status Delet_Student(St_list*st,int copy_ID)
{
    Student_Node*temp;
    Student_Node*scoretemp;

    if(st->pHead==NULL)//Empty
    {
        printf("List is Empty\n");
        return fail;
    }
    Student_Node*search_ = search_Student(st,copy_ID);//step 1 : search for Node
    if(search_==NULL)// not found
	{
        printf("Sorry,Not found\n");
		return fail;
	}

    else // Found
    {
        ///////////////Alphabetical
        if(st->pHead==st->pTail)//only one node
        {
            temp = st->pHead;
            st->pHead=st->pTail=NULL;
        }
        else if(copy_ID == st->pHead->data->ID)//delete Head
           {
               temp =st->pHead;
               //step 1 : assign new head
               st->pHead = st->pHead->pNext;
               //step 2 : new head prev must be NULL
               st->pHead->pPrev=NULL;
               //temp->pNext=NULL;
           }

           else if(copy_ID==st->pTail->data->ID)//delete Tail
           {

               temp = st->pTail;
               //step 1 : assign new Tail
               st->pTail = st->pTail->pPrev;
               //step 2 : new Tail next must be NULL
               st->pTail->pNext=NULL;
           }
           else//middle
           {
               temp = st->pHead;
               while(temp!=NULL&&copy_ID!=temp->data->ID)
               {
                   temp=temp->pNext;
               }
               if(temp->data->ID == copy_ID)
               {
                   temp->pPrev->pNext = temp->pNext;
                   temp->pNext->pPrev = temp->pPrev;
               }
           }

           ///////cs_score
           if(st->score_Head==st->score_Tail)//only one node
            {
                scoretemp = st->score_Head;
                st->score_Head=st->score_Tail=NULL;
            }
            else
            {
                if(copy_ID==st->score_Head->data->ID) //Head score
           {
               scoretemp = st->score_Head;
               st->score_Head = st->score_Head->pright;
               st->score_Head->pleft=NULL;
               scoretemp->pright=NULL;
           }
           else if(copy_ID==st->score_Tail->data->ID) //Tail_score
           {

               scoretemp=st->pTail;
               st->score_Tail = st->score_Tail->pleft;
               st->score_Tail->pright=NULL;
               scoretemp->pleft=NULL;
           }
           else //middlescore
           {
               //scoretemp = st->score_Head;
               scoretemp = st->score_Head;
               while(scoretemp!=NULL&&copy_ID!=scoretemp->data->ID)
               {
                   scoretemp = scoretemp->pright;
               }
               if(scoretemp->data->ID == copy_ID)
               {
                   scoretemp->pleft->pright = scoretemp->pright;
                   scoretemp->pright->pleft = scoretemp->pleft;
               }
            }


           }
           free(temp);
           st->list_size--;
           return success;
    }
}

status Student_Edit(St_list*st,int copy_ID)
{
    if(st->pHead==NULL) //Empty
    {
        printf("Sorry,List is Empty\n");
        return fail;;
    }
    //NOt Empty
    int select =0;
    //search for node
    struct Student_Node*temp = st->pHead;
    while(temp!=NULL&&copy_ID!=temp->data->ID)
    {
        temp = temp->pNext;
    }
        if(temp->data->ID == copy_ID)
        {
            printf("\n====================\n");
            printf("please,Enter number of choice to edit\n");
            printf("1-Address 2-Date 3-Phone Number\n");
            scanf("%d",&select);
            switch(select)
            {

                case ADDRESS:
                    printf("Please,Enter new Address\n");
                    scanf("%s",temp->data->address);
                    break;
                case DATE:
                    printf("Please,Enter new Date as DD/MM/YY \n");
                    scanf("%d/%d/%d",&temp->data->day,&temp->data->month,&temp->data->year);
                    break;
                case PHONE_NO:
                    printf("Please,Enter new Phone Number\n");
                    scanf("%d",&temp->data->phoneno);
                    break;
            }
        }
    return success;

}


status STUDENT_SCORE(St_list*st)
{
    Student_Node*temp = st->pHead;
    int select=0,choose,copy_ID;
    if(st->pHead==NULL) //Empty
    {
        printf("Sorry,List is Empty\n");
        return fail;;
    }
    //Not Empty
    printf("\n====================\n");
    printf("Do you want to update score of specific student or for all students?\n");
    printf("1-for student\n2-for all\n");
    scanf("%d",&choose);
    if(choose==1)//for student
    {
        printf("\n====================\n");
        printf("Please,Enter ID of student\n");
        scanf("%d",&copy_ID);
        Student_Node*search_ = search_Student(st,copy_ID); //search for ID
        if(search_==NULL) //ID not found
        {
            printf("Not Found\n");
            return fail;
        }
        //Found
        printf("Do you want to Edit\n1-CS score\n2-AI score\n3-OS score\n");
        scanf("%d",&select);
        switch(select)
        {
            case cs:
                printf("Please Enter new score of student with ID:%d\n",search_->data->ID);
                scanf("%lf",&search_->score->cs_score);
                int id_copy=search_->data->ID;
                int day_copy = search_->data->day;
                int month_copy = search_->data->month;
                int year_copy = search_->data->year;
                int phone_copy = search_->data->phoneno;
                char name_copy[SIZE] ;
                strcpy(name_copy,search_->data->name);
                char address_copy[SIZE];
                strcpy(address_copy,search_->data->address);
                double cs_copy = search_->score->cs_score;
                double ai_copy =   search_->score->AI_score;
                double os_copy = search_->score->OS_score;
                Delet_Student(st,id_copy);
                New_Student(st,id_copy,day_copy,month_copy,year_copy,phone_copy,name_copy,address_copy,cs_copy,ai_copy,os_copy);
                break;
            case ai :
                printf("Please Enter new score of student with ID:%d\n",search_->data->ID);
                scanf("%lf",&search_->score->AI_score);
                break;
            case os:
                printf("Please Enter new score of student with ID:%d\n",search_->data->ID);
                scanf("%lf",&search_->score->OS_score);
                break;
        }

    }
    else if(choose==2) //for all Students
    {
         printf("\n====================\n");
        printf("please,Enter number of choice to update\n");
        printf("1-CS 2-AI 3-OS\n");
        scanf("%d",&select);
        switch(select)
        {
            case cs:
                for(;temp!=NULL;temp=temp->pNext)
                {
                    printf("Please Enter new score of student with ID:%d\n",temp->data->ID);
                    scanf("%lf",&temp->score->cs_score);
                    int id_copy=temp->data->ID;
                int day_copy = temp->data->day;
                int month_copy = temp->data->month;
                int year_copy = temp->data->year;
                int phone_copy = temp->data->phoneno;
                char name_copy[50] ;
                strcpy(name_copy,temp->data->name);
                char address_copy[50];
                strcpy(address_copy,temp->data->address);
                double cs_copy = temp->score->cs_score;
                double ai_copy =   temp->score->AI_score;
                double os_copy = temp->score->OS_score;
                Delet_Student(st,id_copy);
                New_Student(st,id_copy,day_copy,month_copy,year_copy,phone_copy,name_copy,address_copy,cs_copy,ai_copy,os_copy);
                }
                break;
            case ai :
                for(;temp!=NULL;temp=temp->pNext)
                {
                    printf("Please Enter new score of student with ID:%d\n",temp->data->ID);
                    scanf("%lf",&temp->score->AI_score);
                }
                break;
            case os:
                for(;temp!=NULL;temp=temp->pNext)
                {
                    printf("Please Enter new score of student with ID:%d\n",temp->data->ID);
                    scanf("%lf",&temp->score->OS_score);
                }
                break;
        }
    }
    else
        printf("Wrong choice\n");

    return success;
}
