#include<stdio.h>
#include<iostream>

#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0

using namespace std;

class HeapItem
{
    public:
        int data;                //actual data that is stored
        float key;              //key value of the data, heap is constructed based on key
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:

    HeapItem *A;        //stores heap items, e.g., nodes
    int heapLength;
    int *map;


    //---------------------------------------------------------------------------------------------
    //constructor
    MinHeap()
    {
        A = new HeapItem[MAX_HEAP_SIZE];
        map = new int[MAX_HEAP_SIZE];
        heapLength=0;
    }
    //---------------------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------------------
    //destructor
    ~MinHeap()
    {
        if(map) delete [] map;
        if(A) delete [] A;
        map = 0;                        //set to NULL after deletion
        A = 0;                            //set to NULL after deletion
    }
    //---------------------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------------------
    //Fills the heap with an array of integers
    //key values do not maintain heap property
    void initialize(int v[], int n)
    {
        heapLength = n;
        for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
        {
            A[i+1].data = v[i];
            A[i+1].key = MAXREAL;
            map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
        }
    }
    //---------------------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------------------
    //insert an item
    void insertItem(int data, int key)
    {
        heapLength++;
        A[heapLength].data=data;
        A[heapLength].key=key;

        map[A[heapLength].data]=heapLength;

        //restore the properties of the heap
        buHeapify(heapLength);
    }
    //---------------------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------------------
    //this function removes (and returns) the node which contains the minimum key value
    HeapItem removeMin()
    {
        HeapItem temp=A[1];
        A[1]=A[heapLength];

        if(heapLength==0)
        {
            printf("Nothing to delete\n");
            temp.data=-1;temp.key=-1;
            return  temp;
        }

        heapLength--;
        heapify(1);

        return temp;
    }
    //---------------------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------------------
    //The function updates the key value of an existing data stored in the heap
    void updateKey(int data, float key)
    {
        if(!map[data])
        {
            printf("Data not found\n");
            return ;
        }

        //search
        int idx;
        for(int i=1;i<=heapLength;i++)
        {
            if(data==A[i].data)
            {
                idx=i;
                break;
            }
        }

        A[idx].key=key;
        buHeapify(idx);
        heapify(idx);

    }
    //---------------------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------------------
    //This function returns the key value of a data stored in heap
    float getKey(int data)
    {
        int i = map[data];
        return A[i].key;
    }
    //---------------------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------------------
    //this function will restore heap property
    //works only for updating or removing min
    //adding heapify(i+1);heapify(i+2) before "break" of line 147 will make it work for insert() too.
    void heapify(int i)
    {
        int l,r,smallest;
        while(1)
        {
            l=2*i;          //left child index
            r=2*i+1;     //right child index
            smallest=i;

            if(l>heapLength && r>heapLength)
                break; //nothing to do, we are at bottom

            else if(r>heapLength)
                smallest = l;

            else if(l>heapLength)
                smallest = r;

            else if( A[l].key < A[r].key )
                smallest = l;

            else
                smallest = r;

            if(A[i].key <= A[smallest].key)
                break;	//we are done heapifying

            else
            {
                //swap nodes with smallest child, adjust map array accordingly
                HeapItem t;
                t=A[i];
                A[i]=A[smallest];
                map[A[i].data]=i;
                A[smallest]=t;
                map[A[smallest].data]=smallest;
                i=smallest;
            }
        }
    }
    //---------------------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------------------
    //restoring heap properties starting from index i to the root
    void buHeapify(int i)
    {
        HeapItem temp;
        int parent,child;

        child=i;
        while(child>1)
        {
            //i be the parent, then 2i is the left child, 2i+1 the right
            if(child%2==0)
                parent=child/2;
            else
                parent=(child-1)/2;

            if(A[parent].key>A[child].key)
            {
                temp=A[child];
                A[child]=A[parent];
                A[parent]=temp;

                map[A[parent].data]=parent;
                map[A[child].data]=child;

            }

            child=parent;
        }
    }
    //---------------------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------------------
    //print the heap
    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1; i<=heapLength; i++)
        {
            printf("(%d,%.2f) ", A[i].data, A[i].key);
        }
        printf("\n");
    }
    //---------------------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------------------
    bool Empty()
    {
        if(heapLength==0)
            return true;

        else
            return false;
    }
    //---------------------------------------------------------------------------------------------

};


int main()
{
    //freopen("test.txt","r",stdin);
    int choice,data;
    float key;
    MinHeap heap;
    bool exit = false;

    while(!exit)
    {
        printf("1. Insert 2. RemoveMin 3.Update 4. Print 5. Exit.\n");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                scanf("%d%f",&data,&key);
                heap.insertItem(data, key);
                heap.printHeap();
                break;

            case 2:
                HeapItem item;
                item = heap.removeMin();
                printf("Removed: (%d,%.2f)\n", item.data, item.key);
                heap.printHeap();
                break;

            case 3:
                scanf("%d%f",&data,&key);
                heap.updateKey(data,key);
                heap.printHeap();
                break;

            case 4:
                heap.printHeap();
                break;

            case 5:
                exit = true;
                break;
        }
    }

    return 0;
}
