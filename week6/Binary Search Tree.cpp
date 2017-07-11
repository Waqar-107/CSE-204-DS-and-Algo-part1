/**implementing binary search tree**/
/**1505107**/


#include<stdio.h>
#include<stdlib.h>


#define FALSE_VALUE 0
#define TRUE_VALUE   1


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
int deleteItem(struct treeNode * node, int item)
{
    bool right=false;
    struct treeNode *temp,*prev,*temp2;

    temp=searchItem(root,item);
    if(temp==0)
    {
        return FALSE_VALUE;
    }

    temp=root;prev=0;

    while(true)
    {
        if(item==temp->item)
            break;

        prev=temp;

        if(temp->item<item)
        {
            temp=temp->right;
            right=true;
        }

        else
        {
            temp=temp->left;
            right=false;
        }
    }


    //the item is not found
    if(temp==0)
        return FALSE_VALUE;

    //the item has just left child
    if(temp->left!=0 && temp->right==0)
    {
        temp2=temp->left;

        //if the item is root that is to be deleted
        if(temp==root && prev==0)
        {
            root=temp2;
        }

        else
        {
            prev->left=temp2;
        }

        free(temp);
        return TRUE_VALUE;

    }

    //item has only right child
    if(temp->left==0 && temp->right!=0)
    {
        temp2=temp->right;

        //if the item is root that is to be deleted
        if(temp==root && prev==0)
        {
            root=temp2;
        }

        else
        {
            prev->right=temp2;
        }

        free(temp);
        return TRUE_VALUE;

    }

    //the item is a leaf
    if(temp->left==0 && temp->right==0)
    {
        //the root is the only element
        if(temp==root)
        {
            root=0;
            free(temp);
            return TRUE_VALUE;
        }

        if(right)
            prev->right=0;
        else
            prev->left=0;

        free(temp);

        return TRUE_VALUE;
    }

    //the item has both left and right child
    //the item will be replaced by the minimum of the right sub-tree
    //here the items will be changed and the node where the minimum of right sub-tree is will be freed
    if(temp->left!=0 && temp->right!=0)
    {
        temp2=temp->right;
        prev=temp;

        //if there is just a right child not a sub-tree
        if(temp2->left==0 && temp2->right==0)
        {
            temp->item=temp2->item;
            temp->right=0;
        }

        //if the right child itself has just a right child
        if(temp2->left==0 && temp2->right!=0)
        {
            temp->item=temp2->item;
            temp->right=temp2->right;

            free(temp2);
            return TRUE_VALUE;
        }

        //now the min of right sub-tree
        //here the right child of the item has both right and left child
        while(temp2->left!=0)
        {
            prev=temp2;
            temp2=temp2->left;
        }

        prev->left=0;
        temp->item=temp2->item;

        free(temp2);
        return TRUE_VALUE;

    }

    return TRUE_VALUE;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//returns the minimum item in the tree
int getMinItem()
{
    struct treeNode *temp;
    temp=root;

    //tree has no nodes
    if(root==0)
    {
        return FALSE_VALUE;
    }

    int Min;
    while(temp!=0)
    {
        Min=temp->item;
        temp=temp->left;
    }

    return Min;

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


int main(void)
{
    initializeTree();
    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6.get size. 7.calculate depth of an item.\n");
        printf("8.get min. 9.get max. 10.search in range\n");
        printf("11. PrintInOrder. 12. exit.\n");

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
            int x;
            x=getMinItem();

            if(x==FALSE_VALUE)
                printf("no element found\n ");
            else
                printf("%d is the minimum element\n",x);
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
        {
            break;
        }
    }

    return 0;
}
