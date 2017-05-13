#include<cstdio>

int Merge(int a[],int l,int m,int r)
{
    int i,j,k;
    int n1,n2;
    int local_count=0;

    n1=m-l+1;
    n2=r-m;

    //x and y for left and right sub-array
    int *x,*y;
    x=new int[n1];
    y=new int[n2];

    //---------------------------------copying the sub-arrays
    k=l;
    for(i=0;i<n1;i++)
        x[i]=a[k],k++;

    k=m+1;
    for(i=0;i<n2;i++)
        y[i]=a[k],k++;
    //---------------------------------copying the sub-arrays


    //---------------------------------merging the sub-arrays
    k=l;
    i=0,j=0;
    while(i<n1 && j<n2)
    {
        if(x[i]<=y[j])
        {
            a[k]=x[i];
            i++;
        }

        else
        {
            a[k]=y[j];
            j++;

            local_count+=(n1-i);
        }

        k++;
    }
    //---------------------------------merging the sub-arrays


    //one of the array will be empty but the other won't
    //---------------------------------copying the rest of the items
    for(int w=i;w<n1;w++)
        a[k]=x[w],k++;

    for(int w=j;w<n2;w++)
        a[k]=y[w],k++;
    //---------------------------------copying the rest of the items

    delete[] x;
    delete[] y;

    return local_count;
}

int MergeSort(int a[],int l,int r)
{
    int x=0;
    if(l<r)
    {
        int m=(l+r)/2;

        x+=MergeSort(a,l,m);
        x+=MergeSort(a,m+1,r);

        x+=Merge(a,l,m,r);
    }

    return x;
}

int main()
{
    freopen("in.txt","r",stdin);
    int i,j,k;
    int n;

    scanf("%d",&n);

    int a[n];
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);

    int count=MergeSort(a,0,n-1);

    printf("Total inversion:%d\n",count);

    return 0;
}
