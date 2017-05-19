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
    freopen("in.txt","r",stdin);
    int i,j,k;
    int n,s,f;

    cin>>n;
    pair<int,int> a[n];

    for(i=0;i<n;i++)
    {
        cin>>s>>f;
        a[i]={s,f};
    }

    MergeSort(a,0,n-1);

    vector<pair<int,int>> v;
    v.push_back(a[0]);

    j=0;
    for(i=1;i<n;i++)
    {
        if(a[i].first>=v[j].second)
        {
            v.push_back(a[i]);
            j++;
        }
    }

    cout<<v.size()<<endl;
    for(i=0;i<v.size();i++)
        cout<<v[i].first<<" "<<v[i].second<<endl;

    return 0;
}
