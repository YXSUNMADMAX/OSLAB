#include <stdio.h>
#include <stdlib.h>
#define LEN sizeof(struct node)
struct node{
    int number;
    struct node *next;
};
void output(struct node *head, char *c); //output a linked list
int check(int num, struct node *head);  //find if a element is in a linked list
void output(struct node *head, char *c){
    struct node *p;
    printf("---- elements of %s ----\n",c);
    p=head;
    int count=1;
    while(p!=NULL){
        printf("%d-th element: ",count++);
        printf("%d\n",p->number);
        p=p->next;
    }
}
int check(int num, struct node *head){
    int sign = 0;
    struct node *p;
    p=head;
    while(p!=NULL){
        if(p->number==num) // at the end of the link list p->next=NULL with no object number
            sign=1;
        p=p->next;
    }
    return sign;
}




///////////main//////////
int main(){
    struct node *A_head;
    struct node *A2_head;
    struct node *B_head;
    int A_size, B_size;
    struct node *p1, *p2, *p3;
    int sign=0;
    int i;
    printf("---------------------------------\n");
    printf("----Computing (A-B)union(B-A)----\n");
    printf("---------------------------------\n");
    ////////////input the linked list A and B/////////////
    ///input A
    printf("----input the number of elements of A: ");
    scanf("%d",&A_size);
    A_head=NULL;
    p1=A_head;
    for(i=0;i<A_size;i++){
        p2=(struct node*)malloc(LEN);
        printf("%d-th element: ",i+1);
        scanf("%d",&(p2->number));
        if(sign==0){
            A_head=p2;
            sign=1;
        }
        else{
            p1->next=p2;
        }
        p2->next=NULL;
        p1=p2;
    }
    ///input B
    sign=0;
    printf("----input the number of elements of B: ");
    scanf("%d",&B_size);
    B_head=NULL;
    p1=B_head;
    for(i=0;i<B_size;i++){
        p2=(struct node*)malloc(LEN);
        printf("%d-th element: ",i+1);
        scanf("%d",&(p2->number));
        if(sign==0){
            B_head=p2;
            sign=1;
        }
        else{
            p1->next=p2;
        }
        p2->next=NULL;
        p1=p2;
    }



    /////////copy A to A2//////////////
    sign=0;
    A2_head=NULL;
    p3=A_head;
    p1=A2_head;
    for(i=0;i<A_size;i++){            //<= before error occured
        p2=(struct node*)malloc(LEN);
        p2->number=p3->number;
        if(sign==0){
            A2_head=p2;
            sign=1;
        }
        else{
            p1->next=p2;
        }
        p2->next=NULL;
        p1=p2;
        p3=p3->next;
    }
    //pass

    //////////////A'=A-B///////////////
    p2=p1=A_head;
    sign=0;
    for(i=0;i<A_size;i++){ //p1!=NULL){
        if(check(p1->number,B_head)){ //if this element is in B// 修复一堆内存泄漏 同时检出逻辑错误 应当为检出则删除
            if(sign==0){
                p1=A_head->next;
                p2=p1;
                free(A_head);
                A_head=p2;  //解决了原来直接将head后移的内存泄漏问题
            }
            else{
                p2->next=p1->next;
                p3=p1;
                p1=p1->next;
                free(p3);
            }
        }
        else{
            if(sign==0){
                p1=p1->next;
                sign=1;
            }
            else{
                p2=p2->next;
                p1=p1->next;
            }
        }

    }
    output(A_head,"A-B");





    //////////////B'=B-A2///////////////
    p2=p1=B_head;
    sign=0;
    for(i=0;i<B_size;i++){
        if(check(p1->number,A2_head)){ //修复了一堆内存泄漏 检出逻辑错误
            if(sign==0){
                p1=B_head->next;
                p2=p1;
                free(B_head);
                B_head=p2;
            }
            else{
                p2->next=p1->next;
                p3=p1;
                p1=p1->next;
                free(p3);
            }
        }
        else{
            if(sign==0){
                p1=p1->next;
                sign=1;
            }
            else{
                p2=p2->next;
                p1=p1->next;
            }
        }
    }
    output(B_head,"B-A");



    ///////////computing (A-B)union(B-A), i.e., A' union B'/////////
    if(A_head==NULL)
        A_head=B_head;
    else if (A_head!=NULL && B_head!=NULL){
        p1=A_head;
        while(p1->next!=NULL){
            p1=p1->next;
        }
        p1->next=B_head;
    }
    output(A_head,"(A-B)union(B-A)");

    system("pause");
    return 0;
}
//tag:LGTM