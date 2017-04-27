/*graph implementation using adjacency matrix*/


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
    int * data;
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


//----------------------------------------------------------------------------------Graph class starts here
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    int **matrix ; //adjacency matrix to store the graph
    int *color,*parent,*dist;
    int *start,*finish,time;


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
    void dfs(int source);
    void dfsDriver();
};

//--------------------------------------------------Constructing
Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    matrix = 0 ;
    directed = dir ; //set direction of the graph
    color=0;
    parent=0;
    dist=0;
    start=0;finish=0;time=0;
}
//--------------------------------------------------Constructing


//--------------------------------------------------Memory allocation
void Graph::setnVertices(int n)
{
    this->nVertices = n ;

    //allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

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
    //out of range
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
        return;

    this->nEdges++;
    matrix[u][v] =1;

    if(!directed)
        matrix[v][u] = 1;

}
//--------------------------------------------------Add Edge


//--------------------------------------------------Remove Edge
void Graph::removeEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
        return;

    matrix[u][v]=0;

    if(!directed)
        matrix[v][u]=0;
}
//--------------------------------------------------Remove Edge


//--------------------------------------------------Edge
bool Graph::isEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
        return false;

    if(matrix[u][v]==1 || matrix[v][u]==1)
        return true;
    else
        return false;
}
//--------------------------------------------------Edge


//--------------------------------------------------Degree
int Graph::getDegree(int u)
{
    int count=0;

    if(u<0 || u>=nVertices)
        return 0;

    for(int i=0; i<nVertices; i++)
    {
        if(matrix[u][i])
            count++;
    }

    return count;
}
//--------------------------------------------------Degree


//--------------------------------------------------Finding common node
bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
        return false;

    for(int i=0; i<nVertices; i++)
    {
        //a common adjacent found
        if(matrix[u][i]==1 && matrix[v][i]==1)
            return true;
    }

    return false;

}
//--------------------------------------------------Finding common node


//--------------------------------------------------BFS
void Graph::bfs(int source)
{
    int item;
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
        for(int i=0; i<nVertices; i++)
        {
            if(matrix[u][i]==1 && dist[i]>dist[u]+1 && color[i]==WHITE)
            {
                dist[i]=dist[u]+1;
                q.enqueue(i);

                parent[i]=u;color[i]=GREY;
            }
        }
    }
}
//--------------------------------------------------BFS


//--------------------------------------------------Get Distance
int Graph::getDist(int u, int v)
{
    if(u==v)
        return 0;

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

void Graph::dfs(int source)
{
    time++;
    start[source]=time;
    printf("%d ",source);
    color[source]=GREY;

    for(int i=0;i<nVertices;i++)
    {
        if(matrix[source][i]==1 && color[i]==WHITE)
        {
            parent[i]=source;
            dfs(i);
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
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
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

    if(matrix)
    {
        for(int i=0; i<nVertices; i++)
        {
            delete[] matrix[i];
        }

        //Free the array of pointers
        delete[] matrix;
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
                printf("%d and %d has common vertices.\n",u,v);
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
            printf("Running DFS\n");
            g.dfsDriver();
        }

        else if(ch==8)
            g.printGraph();

        else if(ch==9)
            break;
    }

    return 0;

}
