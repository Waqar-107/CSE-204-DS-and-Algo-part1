/*implementing ArrayList*/
/*1505107*/

#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>

using namespace std;

#define dbg printf("in");

int Size=10;
class ArrayList
{
    int i,j,k;
    int n,len;
    int *a,*temp;

    Malloc()
    {
        temp=new int[Size];

        //copying into temporary array
        for(i=0;i<n;i++)
            temp[i]=a[i];


        delete[] a;
        //allocating more memory to the original
        a=new int[Size];

        //assigning temporary to original
        for(i=0;i<n;i++)
            a[i]=temp[i];

        delete[] temp;

    }

    public:
        ArrayList()
        {
            len=Size;
            a=new int[len];
            n=0;
        }

        void insertItem(int x)
        {
            if(n==Size)
            {
                Malloc();
            }

            a[n]=x;n++;
            print();
            cout<<endl;
        }

        void insertItemAtPos(int x,int p)
        {
            if(n==Size)
                Malloc();

            for(i=n;i>p;i--)
                a[i]=a[i-1];

            a[p]=x;n++;
            print();
            cout<<endl;
        }

        int deleteItem()
        {
            //only one element in the list and waiting to insert another at position 1
            if(n==1)
                cout<<"Empty List!"<<endl;

            n--;
            print();
            cout<<endl;
            return n;
        }

        int deleteFirstItem(int x)
        {
            for(i=0;i<n;i++)
            {
                if(a[i]==x)
                {
                    for(j=i;j<n-1;j++)
                        a[j]=a[j+1];

                    n--;
                    print();
                    cout<<endl;
                    return x;
                }
            }

            cout<<"Element Not Found"<<endl;
            return -1;
        }

        int deleteLastItem(int x)
        {
            for(i=n-1;i>=0;i--)
            {
                if(a[i]==x)
                {
                    for(j=i;j<=n-1;j++)
                        a[j]=a[j+1];

                    n--;
                    print();
                    cout<<endl;
                    return x;
                }
            }

            cout<<"Element Not Found"<<endl;
            return -1;
        }

        void clearList()
        {
            n=0;
            cout<<"Clear Completed"<<endl;
        }

        int searchItem(int x)
        {
            for(i=0;i<n;i++)
            {
                if(x==a[i])
                {
                    cout<<"Found At Position "<<i<<endl;
                    return i;
                }
            }

            cout<<"Not Found"<<endl;
            return -1;
        }

        void print()
        {
            for(i=0;i<n;i++)
                cout<<a[i]<<" ";
        }

        ~ArrayList()
        {
            delete[] a;
        }

};

int strlen(string s)
{
    int l=0,i,x;

    i=0;
    while(s[i]!='\0')
    {
        i++;l++;
    }

    return l;
}

int strToNum(string s)
{
    int i,j,k;
    int n;
    bool positive=true;

    n=0;j=1;
    for(i=strlen(s)-1;i>0;i--)
    {
        if(s[i]==' ')
            break;

        if(s[i]=='-')
        {
            positive=false;
            break;
        }

        else
        {
            //ASCII of 0=48;
            n+=(s[i]-48)*j;
            j*=10;
        }
    }

    if(!positive)
        n=n*(-1);

    return n;
}

int main()
{
    //freopen("in.txt","r",stdin);
    int i,j,k;
    int y,z,idx;
    char ch;
    string s;
    ArrayList w;

    while(true)
    {
        getline(cin,s);
        ch=s[0];

        if(ch=='I')
        {
            bool positive=true;
            j=1;y=0;z=0;
            for(i=strlen(s)-1;;i--)
            {
                if(s[i]=='-')
                {
                    positive=false;continue;
                }

                if(s[i]==' ')
                {
                    idx=i;break;
                }

                y+=(s[i]-48)*j;j*=10;
            }

            if(!positive)
                y*=(-1);

            //only on number is given so inserting it.
            if(idx==1)
            {
                w.insertItem(y);
            }

            else
            {
                z=0;j=1;positive=true;
                for(i=idx-1;i>1;i--)
                {
                    if(s[i]=='-')
                    {
                        positive=false;break;
                    }

                    z+=(s[i]-48)*j;j*=10;
                }

                if(!positive)
                    z*=(-1);

                w.insertItemAtPos(z,y);
            }
        }

        else if(ch=='D')
        {
            if(strlen(s)==1)
                w.deleteItem();

            else
            {
                //D F .....; F in index 2
                if(s[2]=='F')
                {
                    int x=strToNum(s);
                    w.deleteFirstItem(x);
                }

                else
                {
                    int x=strToNum(s);
                    w.deleteLastItem(x);
                }
            }
        }

        else if(ch=='S')
        {
            int x=strToNum(s);
            w.searchItem(x);
        }

        else if(ch=='C')
            w.clearList();

        else
            break;
    }

    return 0;
}
