/**interval scheduling**/

#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

void Merge(pair<int,int> a[],int l,int m,int r)
{
    int i,j,k;
    int n1,n2;

    n1=m-l+1;
    n2=r-m;

    //creating two temporary sub-arrays x and y
    pair<int,int> x[n1],y[n2];

    k=l;
    for(i=0;i<n1;i++)
    {
        x[i]=a[k];
        k++;
    }

    k=m+1;
    for(i=0;i<n2;i++)
    {
        y[i]=a[k];
        k++;
    }


    //merging the sub-arrays
    i=0;j=0;k=l;
    while(i<n1 && j<n2)
    {
        if(x[i].second<y[j].second)
        {
            a[k]=x[i];
            i++;
        }

        else
        {
            a[k]=y[j];
            j++;
        }

        k++;
    }


    //copying the remaining elements in an array, the other one is empty by now :)
    while(i<n1)
    {
        a[k]=x[i];
        i++;k++;
    }

    while(j<n2)
    {
        a[k]=y[j];
        j++;k++;
    }
}

void MergeSort(pair<int,int> a[],int l,int r)
{
    if(l<r)
    {
        int m = (l+r)/2;

        MergeSort(a,l,m);
        MergeSort(a,m+1,r);

        Merge(a,l,m,r);
    }
}

int main()
{
    //freopen("in.txt","r",stdin);
    int i,j,k;
    int n,s,f;
    int count=0;

    cin>>n;
    pair<int,int> a[n];

    for(i=0;i<n;i++)
    {
        cin>>s>>f;
        a[i]={s,f};
    }

    MergeSort(a,0,n-1);

    pair<int,int> v[n];
    v[0]=a[0];
    count++;

    j=0;
    for(i=1;i<n;i++)
    {
        if(a[i].first>=v[j].second)
        {
            j++;
            v[j]=a[i];
            count++;
        }
    }

    cout<<count<<endl;
    for(i=0;i<count;i++)
        cout<<v[i].first<<" "<<v[i].second<<endl;

    return 0;
}
