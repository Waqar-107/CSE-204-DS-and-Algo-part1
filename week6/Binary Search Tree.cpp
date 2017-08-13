/**implementing binary search tree**/
/**1505107**/


#include<stdio.h>
#include<stdlib.h>
#include<queue>


#define FALSE_VALUE 0
#define TRUE_VALUE   1

using namespace std;
//-------------------------------------------------------------------
struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};
//-------------------------------------------------------------------

struct treeNode *root;

//-------------------------------------------------------------------
void initializeTree()
{
    root = 0;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
struct treeNode *searchItem(struct treeNode *node, int item)
{
    if(node==0)
        return 0;

    if(node->item==item)
        return node;            //found, return node

    struct treeNode *t = 0;

    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree

    return t;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
struct treeNode *makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
struct treeNode * insertItem(struct treeNode *node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
int calcNodeHeight(struct treeNode *node) //return height of a node
{
    if(node==0)
        return -1;

    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);

    if(l>r)
        return l+1;

    else
        return r+1;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode *node = 0;
    node = searchItem(root, item);

    if(node==0)
        return -1; //not found

    else
        return calcNodeHeight(node);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//the total number of nodes in the tree
int getSize(struct treeNode *node)
{
    if(node==0)
        return 0;

    return 1+getSize(node->left)+getSize(node->right);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//return depth of a node
int calcNodeDepth(struct treeNode *node)
{
    struct treeNode *temp;
    temp=root;

    int Count=0;

    while(temp!=0)
    {
        if(temp->item==node->item)
            break;

        if(temp->item>node->item)
            temp=temp->left;

        else
            temp=temp->right;

        Count++;

    }

    return Count;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//return depth of an item in the tree
int calcDepth(int item)
{
    struct treeNode *node;
    node=searchItem(root,item);

    //element don't exists
    if(node==0)
        return -1;

    if(node==root)
        return 0;

    return calcNodeDepth(node);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//returns the minimum item in the tree
treeNode *getMinItem(struct treeNode *node)
{
    struct treeNode *temp;
    temp=node;

    while(temp->left!=0)
    {
        temp=temp->left;
    }

    return temp;

}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
int deleteItem(struct treeNode * node, int item)
{
    treeNode *pi;
    treeNode *temp=searchItem(node,item);

    if(!temp)
    {
        return FALSE_VALUE;
    }

    //if temp has only one child or no child at all
    if((temp->left!=0 && temp->right==0) || (temp->left==0 && temp->right!=0) || (temp->left==0 && temp->right==0))
    {
        //find temps parent
        pi=node;
        bool f=1;

        while(pi)
        {
            if(pi->left!=0 && (pi->left)->item==item)
                break;

            else if(pi->right!=0 && (pi->right)->item==item)
            {
                f=0;break;
            }

            if(item>(pi->item))
                pi=pi->right;
            else
                pi=pi->left;

        }

        if(temp->left!=0 && temp->right==0)
        {

            if(f)
                pi->left=temp->left;
            else
                pi->right=temp->left;
        }

        else if(temp->left==0 && temp->right!=0)
        {
            if(f)
                pi->left=temp->right;
            else
                pi->right=temp->right;
        }

        else
        {
            if(f)
                pi->left=0;
            else
                pi->right=0;
        }

        free(temp);
    }

    else
    {
        treeNode *m=getMinItem(temp->right);
        int x=m->item;
        deleteItem(root,m->item);

        temp->item=x;
    }

     return TRUE_VALUE;

}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//returns the maximum item in the tree
int getMaxItem()
{
    struct treeNode *temp;
    temp=root;

    //tree has no nodes
    if(root==0)
    {
        return FALSE_VALUE;
    }

    int Max;
    while(temp!=0)
    {
        Max=temp->item;
        temp=temp->right;
    }

    return Max;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//search in the specified range
int rangeSearch(struct treeNode *node, int leftBound, int rightBound)
{
    if(node==0)
        return 0;

    if(node->item>=leftBound && node->item<=rightBound)
        return 1+rangeSearch(node->left,leftBound,rightBound)+rangeSearch(node->right,leftBound,rightBound);
    else
         return rangeSearch(node->left,leftBound,rightBound)+rangeSearch(node->right,leftBound,rightBound);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
void printInOrder(struct treeNode * node, int height)
{
    if(node==0)
        return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0;i<height;i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}
//-------------------------------------------------------------------

queue<treeNode*> q;
void levelOrder()
{
    if(root!=0)
        q.push(root);

    while(!q.empty())
    {
        struct treeNode *temp;
        temp=q.front();
        q.pop();

        printf("%d ",temp->item);

        if(temp->left)
            q.push(temp->left);
        if(temp->right)
            q.push(temp->right);
    }

    printf("\n");
}

void printPostOrder(struct treeNode *temp)
{
    if(temp->left==0 && temp->right==0)
    {
        printf("%d ",temp->item);
        return;
    }

    if(temp->left)
        printPostOrder(temp->left);

    if(temp->right)
        printPostOrder(temp->right);

    printf("%d ",temp->item);
}

void printPreOrder(struct treeNode *temp)
{
    if(temp->left==0 && temp->right==0)
    {
        printf("%d ",temp->item);
        return;
    }

    printf("%d ",temp->item);

    if(temp->left)
        printPreOrder(temp->left);
    if(temp->right)
        printPreOrder(temp->right);
}

int main(void)
{
    //freopen("in.txt","r",stdin);


    initializeTree();
    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6.get size. 7.calculate depth of an item.\n");
        printf("8.get min. 9.get max. 10.search in range\n");
        printf("11. In-OrderTraversal. 12. Level-Order traversal. 13Pre-Order. 14.Post-Order\n");
        printf("15.Exit\n\n");

        int ch;
        scanf("%d",&ch);

        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }

        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(root, item);
        }

        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);

            if(res!=0)
                printf("Found.\n");

            else
                printf("Not found.\n");
        }

        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }

        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }

        else if(ch==6)
        {
            int x;
            x=getSize(root);
            printf("Size of the tree: %d\n",x);
        }

        else if(ch==7)
        {
            int item;
            scanf("%d", &item);
            int depth = calcDepth(item);
            printf("Depth of %d = %d\n", item, depth);
        }

        else if(ch==8)
        {
            treeNode *x;
            x=getMinItem(root);

            if(x==0)
                printf("no element found\n ");
            else
                printf("%d is the minimum element\n",x->item);
        }

        else if(ch==9)
        {
            int x;
            x=getMaxItem();

            if(x==FALSE_VALUE)
                printf("no element found\n ");
            else
                printf("%d is the maximum element\n",x);
        }

        else if(ch==10)
        {
            int lb,rb;
            scanf("%d%d",&lb,&rb);

            printf("%d items present in the range.\n",rangeSearch(root,lb,rb));
        }

        else if(ch==11)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }

        else if(ch==12)
            levelOrder(),printf("\n");

        else if(ch==13)
        {
            printf("preOrder------------------------------------------------------------------------\n");
            printPreOrder(root);
            printf("\npreOrder------------------------------------------------------------------------\n");
        }

        else if(ch==14)
        {
            printf("postOrder------------------------------------------------------------------------\n");
            printPostOrder(root);
            printf("\npostOrder------------------------------------------------------------------------\n");
        }

        else if(ch==15)
            break;
    }

    return 0;
}
