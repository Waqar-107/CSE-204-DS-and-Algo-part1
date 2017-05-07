#include<iostream>
using namespace std;

int Merge(int a[],int l,int m,int r,int count)
{
    int i,j,k;
    int n1=m-l+1;
    int n2=r-m;
    int local_count=0;

    int L[n1],R[n2];

    k=l;
    for(i=0;i<n1;i++)
    {
        L[i]=a[k];
        k++;
    }


    k=m+1;
    for(i=0;i<n2;i++)
    {
        R[i]=a[k];
        k++;
    }

    //merge into one array
    //counting inversions
    i=0;j=0;k=l;
    while(i<n1 && j<n2)
    {
        //elements placed in right order
        if(L[i]<=R[j])
        {
            a[k]=L[i];i++;
        }

        else
        {
            a[k]=R[j];j++;
            local_count+=(n1-i);
        }

        k++;
    }

    while(i<n1)
    {
        a[k]=L[i];i++;k++;
    }

    while(j<n2)
    {
        a[k]=R[j];j++;k++;
    }

    return count+local_count;
}

int MergeSort(int a[],int l,int r,int count)
{
    int x=0;
    if(l<r)
    {
        int m=(l+r)/2;

        x+=MergeSort(a,l,m,count);
        x+=MergeSort(a,m+1,r,count);

        x+=Merge(a,l,m,r,count);
    }

    return x;
}

int main()
{
    int n;

    cin>>n;
    int a[n];

    for(int i=0;i<n;i++)
        cin>>a[i];

    int count=MergeSort(a,0,n-1,0);

    for(int i=0;i<n;i++)
        cout<<a[i]<<" ";

    cout<<endl;
    cout<<"inversion:"<<count<<endl;

    return 0;

}
