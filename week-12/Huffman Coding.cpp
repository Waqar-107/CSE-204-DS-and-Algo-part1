#include<cstdio>
#include<iostream>
#include<map>

#define MAX_HEAP_SIZE 100000
#define dbg printf("in\n");

using namespace std;

class HeapItem
{
    public:
        string data;          //actual character saved as string as the internal nodes will contain more than one char
        int key;
        string left,right;   //left and right indicates who is on left and who is on right of a node, if leaf then -1,-1.
        bool internal;
        string s="";          //'s' saves the Huffman code.
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:

    HeapItem *A;
    int heapLength;

    //---------------------------------------------------------------------------------------------
    //constructor
    MinHeap()
    {
        A = new HeapItem[MAX_HEAP_SIZE];
        heapLength=0;
    }
    //---------------------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------------------
    //destructor
    ~MinHeap()
    {
        if(A) delete [] A;
        A = 0;
    }
    //---------------------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------------------
    //insert an item
    void insertItem(HeapItem item)
    {
        heapLength++;
        A[heapLength]=item;

        //restore the properties of the heap
        buHeapify(heapLength);
    }
    //---------------------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------------------
    //this function removes (and returns) the node which contains the minimum key value
    HeapItem removeMin()
    {
        HeapItem temp=A[1];
        swap(A[1],A[heapLength]);

        heapLength--;
        heapify(1);

        return temp;
    }
    //---------------------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------------------
    //this function will restore heap property
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
                //swap nodes with smallest child
                swap(A[i],A[smallest]);
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
            cout<<"("<<A[i].data<<","<<A[i].key<<") ";
        }
        printf("\n");
    }
    //---------------------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------------------
    int Size()
    {
        return heapLength;
    }

};

void Huffman(map<string,HeapItem> mp,string data,int sign,string s)
{
    string str=s;
    HeapItem hp=mp[data];

    if(sign==0)
        str.push_back('0');

    else if(sign==1)
        str.push_back('1');

    if(hp.left=="-1" && hp.right=="-1")
    {
        cout<<hp.data<<" "<<str<<endl;
    }

    else
    {
        Huffman(mp,hp.left,0,str);
        Huffman(mp,hp.right,1,str);
    }

}

int main()
{
    freopen("in.txt","r",stdin);
    int i,j,k;
    int key,n,x;
    string data;
    MinHeap heap;

    cin>>n;

    //-------------------------------------------building the heap initially
    HeapItem hp;
    for(i=0;i<n;i++)
    {
        cin>>data>>key;

        hp.data=data; hp.key=key; hp.internal=false;
        hp.left="-1"; hp.right="-1";

        heap.insertItem(hp);
    }

    //-------------------------------------------building the heap initially

    HeapItem a,b;
    map<string,HeapItem> maxHeap;

    while(heap.Size()>1)
    {
        a=heap.removeMin();
        b=heap.removeMin();

        x=a.key+b.key;

        //making internal nodes
        hp.data=a.data+b.data; hp.key=x ;hp.internal=true;
        hp.left=a.data; hp.right=b.data;

        heap.insertItem(hp);
        maxHeap[a.data]=a;
        maxHeap[b.data]=b;
    }

    a=heap.removeMin();
    maxHeap[a.data]=a;

    Huffman(maxHeap,a.data,2,a.s);

    return 0;
}
