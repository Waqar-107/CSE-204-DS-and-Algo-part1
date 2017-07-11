/**Huffman_coding**/
/**1505107**/

#include<cstdio>
#include<iostream>

#define MAX_HEAP_SIZE 100000
#define dbg printf("in\n");

using namespace std;

class HeapItem
{
    public:
       char data;
       int key;
       HeapItem *left,*right;
};


class MinHeap
{
    public:

        HeapItem **A;
        int heapLength;

        //---------------------------------------------------------------------------------------------
        //constructor
        MinHeap()
        {
            A = new HeapItem*[MAX_HEAP_SIZE];
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
        // insert an item
        void insertItem(HeapItem item)
        {
            heapLength++;
            A[heapLength]=new HeapItem;

            A[heapLength]->data=item.data;
            A[heapLength]->key=item.key;
            A[heapLength]->left=item.left;
            A[heapLength]->right=item.right;

            //restore the properties of the heap
            buHeapify(heapLength);
        }
        //---------------------------------------------------------------------------------------------


        //---------------------------------------------------------------------------------------------
        //this function removes (and returns) the node which contains the minimum key value
        HeapItem* removeMin()
        {
            HeapItem* temp=A[1];
            swap(A[1],A[heapLength]);

            heapLength--;
            heapify(1);

            return temp;
        }
        //---------------------------------------------------------------------------------------------


        //---------------------------------------------------------------------------------------------
        //generating Huffman code
        void Huffman(HeapItem* root,int sign,string s)
        {
            string str=s;

            if(sign==0)
                str.push_back('0');

            else if(sign==1)
                str.push_back('1');

            if(root->left==0 && root->right==0)
            {
                cout<<root->data<<" "<<str<<endl;
            }

            else
            {
                Huffman(root->left,0,str);
                Huffman(root->right,1,str);
            }
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

                else if( A[l]->key < A[r]->key )
                    smallest = l;

                else
                    smallest = r;

                if(A[i]->key <=A[smallest]->key)
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
            HeapItem* temp;
            int parent,child;

            child=i;
            while(child>1)
            {
                //i be the parent, then 2i is the left child, 2i+1 the right
                if(child%2==0)
                    parent=child/2;
                else
                    parent=(child-1)/2;

                if(A[parent]->key>A[child]->key)
                {
                    swap(A[parent],A[child]);
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
                cout<<"("<<A[i]->data<<","<<A[i]->key<<") ";
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

int main()
{
    //freopen("in.txt","r",stdin);
    int i,j,k;
    int key,n;
    char data;
    MinHeap heap;

    cin>>n;

    //-------------------------------------------building the heap initially
    HeapItem hp;
    for(i=0;i<n;i++)
    {
        cin>>data>>key;

        hp.data=data; hp.key=key;
        hp.left=0; hp.right=0;

        heap.insertItem(hp);
    }

    //-------------------------------------------building the heap initially


    //-------------------------------------------building the Huffman tree
    char ch='#';
    HeapItem *a,*b;
    while(heap.Size()>1)
    {
        a=heap.removeMin();
        b=heap.removeMin();

        hp.data=ch;hp.key=a->key+b->key;
        hp.left=a;hp.right=b;

        heap.insertItem(hp);
    }
    //-------------------------------------------building the Huffman tree


    //root of the tree
    a=heap.removeMin();
    heap.Huffman(a,2,"");

    return 0;
}
