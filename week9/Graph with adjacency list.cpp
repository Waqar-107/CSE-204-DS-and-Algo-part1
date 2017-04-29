/*graph implementation using adjacency list*/

#include<stdio.h>
#include<stdlib.h>

#define NULL_VALUE -999999
#define INFINITY 999999

#define WHITE 1
#define GREY 2
#define BLACK 3
#define dbg printf("in\n");

//----------------------------------------------------------------------------------Queue class starts here
class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int *data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}

void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0) return true ;
    else return false ;
}


int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//----------------------------------------------------------------------------------Queue class ends here


//----------------------------------------------------------------------------------Dynamic ArrayList
class ArrayList
{
    int * list;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    int getItem(int position) ;
    int getLength();
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new int[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new int[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item )
            return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length ) return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}

void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return ; //nothing to remove
    removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
    if(position < 0 || position >= length) return NULL_VALUE ;
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//----------------------------------------------------------------------------------ArrayList class ends here


//----------------------------------------------------------------------------------Graph class starts here
class Graph
{
    int nVertices, nEdges ;
    int *color,*parent,*dist;
    int time,*start,*finish;
    bool directed ;
    ArrayList  *adjList ;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs(int source); //will run dfs in the graph
    void dfsDriver();
};

//--------------------------------------------------Constructing
Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    directed = dir ; //set direction of the graph
    color=0;parent=0;dist=0;
    start=0;finish=0;time=0;
}
//--------------------------------------------------Constructing


//--------------------------------------------------Memory allocation
void Graph::setnVertices(int n)
{
    this->nVertices=n;

    if(adjList!=0)
        delete[] adjList ; //delete previous list

    //deleting previous statistics of BFS
    if(color!=0)
        delete[] color;

    if(parent!=0)
        delete[] parent;

    if(dist!=0)
        delete[] dist;

    //deleting previous statistics of DFS
    if(start!=0)
        delete[] start;

    if(finish!=0)
        delete[] finish;

    adjList=new ArrayList[nVertices] ;

    color=new int[nVertices];
    dist=new int[nVertices];
    parent=new int[nVertices];

    start=new int[nVertices];
    finish=new int[nVertices];
}
//--------------------------------------------------Memory allocation


//--------------------------------------------------Add Edge
void Graph::addEdge(int u, int v)
{
    //vertex out of range
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        printf("vertex out of range\n");
        return;
    }

    this->nEdges++ ;

    adjList[u].insertItem(v) ;

    if(!directed)
        adjList[v].insertItem(u) ;
}
//--------------------------------------------------Add Edge


//--------------------------------------------------Remove Edge
void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return;

    adjList[u].removeItem(v);

    if(!directed)
        adjList[v].removeItem(u);
}
//--------------------------------------------------Remove Edge


//--------------------------------------------------Edge
bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return false;

    if(adjList[u].searchItem(v)!=NULL_VALUE || adjList[v].searchItem(u)!=NULL_VALUE)
        return true;

    else
        return false;
}
//--------------------------------------------------Edge


//--------------------------------------------------Degree
int Graph::getDegree(int u)
{
    if(u<0 || u>=nVertices)
        return 0;

    return adjList[u].getLength();
}
//--------------------------------------------------Degree


//--------------------------------------------------Finding common node
bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return 0;

    int l,item;
    l=adjList[u].getLength();

    for(int i=0;i<l;i++)
    {
        item=adjList[u].getItem(i);

        //at least one item found so return true.
        if(adjList[v].searchItem(item)!=NULL_VALUE)
            return true;
    }

    return false;
}
//--------------------------------------------------Finding common node


//--------------------------------------------------BFS
void Graph::bfs(int source)
{
    int item,l;
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }

    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;

    q.enqueue(source) ;
    while( !q.empty() )
    {
        int u=q.dequeue();

        color[u]=BLACK;
        l=adjList[u].getLength();
        //each of the node connected with 'u', will be pushed in the queue
        for(int i=0;i<l;i++)
        {
            item=adjList[u].getItem(i);
            if(dist[item]>dist[u]+1 && color[item]==WHITE)
            {
                q.enqueue(item);
                dist[item]=dist[u]+1;

                parent[item]=u;color[item]=GREY;
            }
        }
    }
}
//--------------------------------------------------BFS


//--------------------------------------------------Get Distance
int Graph::getDist(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
        return INFINITY;

    bfs(u);
    return dist[v];
}
//--------------------------------------------------Get Distance


//--------------------------------------------------DFS
void Graph::dfsDriver()
{
    time=0;
    for(int i=0;i<nVertices;i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;

        start[i]=0;finish[i]=0;
    }

    for(int i=0;i<nVertices;i++)
    {
        if(color[i]==WHITE)
            dfs(i);
    }
    printf("\n");

}

void Graph :: dfs(int source)
{
    time++;
    start[source]=time;

    printf("%d ",source);
    color[source]=GREY;
    int l=adjList[source].getLength();

    for(int i=0; i<l; i++)
    {
        if(color[adjList[source].getItem(i)]==WHITE)
        {
            parent[adjList[source].getItem(i)]=source;
            dfs(adjList[source].getItem(i));
        }
    }

    color[source]=BLACK;
    time++;
    finish[source]=time;
}
//--------------------------------------------------DFS


//--------------------------------------------------Print
void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}
//--------------------------------------------------Print


//--------------------------------------------------Destruction
Graph::~Graph()
{
    if(color)
    {
        delete[] color;
        color=0;
    }

    if(parent)
    {
        delete[] parent;
        parent=0;
    }

    if(dist)
    {
        delete[] dist;
        dist=0;
    }

    if(adjList)
    {
        delete[] adjList;
        adjList=0;
    }

    if(finish)
    {
        delete[] finish;
        finish=0;
    }

    if(start)
    {
        delete[] start;
        start=0;
    }
}
//--------------------------------------------------Destruction

//----------------------------------------------------------------------------------Graph class ends here


int main(void)
{
    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. 2.Remove Edge. 3.Is Edge\n");
        printf("4.Degree of a vertex. 5.Has Common Adjacent. 6.Get Distance\n");
        printf("7.Run DFS. 8.Print Graph. 9.Exit.\n");

        int ch;
        scanf("%d",&ch);

        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }

        else if(ch==2)
        {
            int u,v;
            scanf("%d%d", &u, &v);
            g.removeEdge(u, v);
        }

        else if(ch==3)
        {
            int u, v;
            scanf("%d%d", &u, &v);

            if(g.isEdge(u,v))
                printf("Edge between u and v exists.\n");
            else
                printf("No edge between u and v\n");

        }

        else if(ch==4)
        {
            int u;
            scanf("%d",&u);

            printf("Degree of %d is %d\n",u,g.getDegree(u));
        }

        else if(ch==5)
        {
            int u,v;
            scanf("%d%d",&u,&v);

            if(g.hasCommonAdjacent(u,v))
                printf("%d and %d has a common vertex.\n",u,v);
            else
                printf("%d and %d do not have common vertex.\n",u,v);
        }

        else if(ch==6)
        {
            int u,v;
            scanf("%d%d",&u,&v);

            printf("Distance between %d and %d is %d.\n",u,v,g.getDist(u,v));
        }

        else if(ch==7)
        {
            printf("Running DFS:\n");
            g.dfsDriver();
        }

        else if(ch==8)
            g.printGraph();

        else if(ch==9)
            break;
    }

    return 0;

}
