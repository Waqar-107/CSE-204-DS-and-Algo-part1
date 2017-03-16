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


void initializeList()
{
    //initially set to null
    list = 0;
}

//insert at the beginning of the linked list
int insertItem(int item)
{
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;

	newNode->item = item ;
	newNode->next = list ;
	list = newNode ;

	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	struct listNode *temp, *prev ;
	temp = list ; //start at the beginning

	while (temp != 0)
	{
		if (temp->item == item) break ;
		prev = temp;
		temp = temp->next;
	}

	//item not found to delete
	if (temp == 0)
        return NULL_VALUE ;

    //delete the first node
	if (temp == list)
	{
		list = list->next ;
		free(temp) ;
	}

	else
	{
		prev->next = temp->next ;
		free(temp);
	}

	return SUCCESS_VALUE ;
}

//search an item
struct listNode * searchItem(int item)
{
	struct listNode * temp ;
	temp = list ; //start at the beginning

	while (temp != 0)
	{
		if (temp->item == item) return temp ;
		temp = temp->next ; //move to next node
	}
	return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

//print
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


//insert an element at the end
int insertLast(int item)
{
    struct listNode *newItem,*temp;
    newItem=(struct listNode*)malloc(sizeof(struct listNode));

    //list is empty
    if(list==0)
    {
        newItem->item=item;
        newItem->next=list;
        list=newItem;

        return SUCCESS_VALUE;
    }

    //searching for the last element
    temp=list;
    while(temp->next!=0)
    {
        temp=temp->next;
    }

    newItem->item=item;
    newItem->next=temp->next;
    temp->next=newItem;

    return SUCCESS_VALUE;
}


//inserting item before a particular item
int insertBefore(int oldItem, int item)
{
	struct listNode *prev,*newItem,*temp;
	newItem=(struct listNode*)malloc(sizeof(listNode));

	temp=list;prev=0;
	while(temp!=0)
    {
        if(temp->item==oldItem)
            break;

        prev=temp;
        temp=temp->next;
    }

    //list is empty or old element found in the top
    if(temp==list || temp==0)
    {
        newItem->item=item;
        newItem->next=list;
        list=newItem;

        return SUCCESS_VALUE;
    }



    //if found  then the item will be inserted between prev and temp
    newItem->item=item;
    newItem->next=temp;
    prev->next=newItem;

    return SUCCESS_VALUE;
}


//delete after an item
int deleteAfter(int item)
{
	struct listNode *dell,*temp;
	temp=searchItem(item);

	//item not found;
	if(temp==0)
    {
        return NULL_VALUE;
    }

	dell=temp->next;

	//if the element after the last element is asked to delete, it is also not possible
    if(dell==0)
    {
        return NULL_VALUE;
    }

    temp->next=dell->next;
    free(dell);

    return SUCCESS_VALUE;

}


//delete the last element
int deleteLast()
{
    //nothing to delete
    if(list==0)
        return NULL_VALUE;

    struct listNode *temp,*prev;
    temp=list;

    //only one element in the list
    if(temp->next==0)
    {
        list=0;
        free(temp);

        return SUCCESS_VALUE;
    }

    while(temp->next!=0)
    {
        prev=temp;
        temp=temp->next;
    }

    //"prev" has the element before the last element, and temp has the last one
    prev->next=temp->next;  //null;
    free(temp);

    return SUCCESS_VALUE;

}



int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4.Insert at last. 5. Insert before. 6.DeleteAfter.\n7.deleteLast. 8.print. 9. exit.\n");

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

            if(res!=0)
                printf("Found.\n");

            else
                printf("Not found.\n");
        }

        else if(ch==4)
        {
            int x;
            scanf("%d",&x);

            insertLast(x);
        }

        else if(ch==5)
        {
            int x,p;
            scanf("%d%d",&p,&x);

            insertBefore(p,x);
        }

        else if(ch==6)
        {
            int pos;
            scanf("%d",&pos);
            deleteAfter(pos);
        }

        else if(ch==7)
            deleteLast();

        else if(ch==8)
        {
            printList();
        }

        else if(ch==9)
        {
            break;
        }
    }

}
