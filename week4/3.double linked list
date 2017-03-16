#include<stdio.h>
#include<stdlib.h>


#define dbg printf("in");
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999


struct listNode
{
    int item;
    struct listNode *next;
    struct listNode *prev;
};


struct listNode * list;
struct listNode * tail;


void initializeList()
{
    //initially set to null
    list = 0;
    tail = 0;
}

//insert at the beginning
int insertFirst(int item)
{
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;

	if(list==0) //inserting the first item
    {
        newNode->next = 0;
        newNode->prev = 0;
        list = newNode;
        tail = newNode;
    }

    else
    {
        newNode->next = list;
        list->prev = newNode;
        newNode->prev = 0;
        list = newNode;
    }

	return SUCCESS_VALUE ;
}


int deleteAfter(int item)
{
    struct listNode *temp,*del,*last;
    temp=list;

    while(temp!=0)
    {
        if(temp->item==item)
            break;

        temp=temp->next;
    }

    //item not found or only one element in the list
    if(temp==0 || temp->next==0)
        return NULL_VALUE;


    del=temp->next;
    last=del->next;


    //if last is 0 then the last element is being deleted
    if(last==0)
    {
        temp->next=0;
        tail=temp;

        free(del);
        return SUCCESS_VALUE;
    }

    //delete del, which is between temp and last
    temp->next=last;
    last->prev=temp;

    free(del);

    return SUCCESS_VALUE;

}

int deleteLast()
{
    int item;
    struct listNode *temp,*prev;
    temp=tail;

    if(list==0)
        return NULL_VALUE;

    //only one element left to delete;
    if(list->next==0)
    {
        item=temp->item;

        free(temp);
        list=0;
        tail=0;
        return item;
    }

    item=temp->item;
    prev=temp->prev;
    prev->next=temp->next;

    tail=prev;

    free(temp);
    return item;

}


struct listNode * searchItem(int item)
{
	struct listNode * temp ;
	temp = list ;

	while (temp != 0)
	{
		if (temp->item == item) return temp ;
		temp = temp->next ;
	}

	return 0 ;
}


void printListForward()
{
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n");
}


void printListBackward()
{
    struct listNode * temp;
    temp = tail;
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->prev;
    }
    printf("\n");

}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Print forward. 5. Print backward. 6. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertFirst(item);
        }

        else if(ch==2)
        {
            int item = deleteLast();

            if(item!=NULL_VALUE)
                printf("Deleted: %d\n", item);
        }

        else if(ch==3)
        {
            int item;
            scanf("%d", &item);

            struct listNode * res = searchItem(item);

            if(res!=0)
                printf("Found.\n");

            else
                printf("Not found.\n");
        }

        else if(ch==4)
            printListForward();

        else if(ch==5)
            printListBackward();

        else if(ch==6)
            break;

    }

    return 0;

}
