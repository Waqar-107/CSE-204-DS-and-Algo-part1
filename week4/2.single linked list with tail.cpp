#include<stdio.h>
#include<stdlib.h>


#define dbg printf("in");
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999


struct listNode
{
    int item;
    struct listNode *next;
};


struct listNode * list;
struct listNode * tail;


void initializeList()
{
    //initially set to null
    list = 0;
	tail = 0;
}


struct listNode * searchItem(int item)
{
	struct listNode * temp ;
	temp = list ;

	while (temp != 0)
	{
		if (temp->item == item)
            return temp ;

		temp = temp->next ;
	}
	return 0 ;
}


void printList()
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

//insert at the beginning
int insertItem(int item)
{
	//declare and allocate memory
    struct listNode *newItem;
    newItem=(struct listNode*)malloc(sizeof(struct listNode));

    //list is empty and tail needs to be updates
    if(list==0)
    {
        newItem->item=item;
        newItem->next=list;

        list=newItem;
        tail=newItem;

        return SUCCESS_VALUE;
    }

     newItem->item=item;
     newItem->next=list;

     list=newItem;

    return SUCCESS_VALUE;
}

//***
int deleteItem(int item)
{
    struct listNode *temp,*prev;
    temp=list;

    while(temp!=0)
    {
        //item found, break the loop
        if(temp->item==item)
            break;

        prev=temp;
        temp=temp->next;
    }

    //item not found
    if(temp==0)
        return NULL_VALUE;

    //item found at the beginning
    if(temp==list)
    {
        list=list->next;
        free(temp);

        //if the list is empty then tail will change otherwise not
        if(list==0)
            tail=list;
    }

    else
    {
        //if the temp->next is null then the last item is asked to delete thus we need to update the tail
        if(temp->next==0)
            tail=prev;

        prev->next=temp->next;
        free(temp);
    }

    return SUCCESS_VALUE;

}

//delete the element after item
int deleteAfter(int item)
{
	struct listNode *temp;

	//pointer
	temp=searchItem(item);

	//item not found
	if(temp==0)
        return NULL_VALUE;

    //if it is the last element then also it is impossible to delete after
    if(temp->next==0)
        return NULL_VALUE;

    struct listNode *delItem;
    delItem=temp->next;

    if(tail==delItem)
    {
        tail=temp;
    }

    temp->next=delItem->next;

    free(delItem);

    return SUCCESS_VALUE;
}

int insertLast(int item)
{
    struct listNode *newItem,*temp;
    newItem=(struct listNode*)malloc(sizeof(struct listNode));

    if(list==0)
    {
        newItem->item=item;
        newItem->next=list;

        list=newItem;
        tail=newItem;

        return SUCCESS_VALUE;
    }

    temp=tail;
    newItem->item=item;
    newItem->next=temp->next;
    temp->next=newItem;
    tail=newItem;

    return SUCCESS_VALUE;
}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4.delete After. 5.insert last  6. Print.7. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }

        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }

        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }

        else if(ch==4)
        {
            int item;
            scanf("%d", &item);

            deleteAfter(item);
        }

        else if(ch==5)
        {
            int item;
            scanf("%d", &item);

            insertLast(item);
        }

        else if(ch==6)
        {
            printList();
        }
        else if(ch==7)
        {
            break;
        }
    }

    return 0;

}
