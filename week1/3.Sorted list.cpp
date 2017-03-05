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
    int mid,low,high;
    int *a,*temp;

    Malloc()
    {
        Size*=2;
        temp=new int[Size];

        //copying into temporary array
        for(i=0;i<n;i++)
            temp[i]=a[i];


        //allocating more memory to the original
        a=new int[Size];


        //copying back from temp
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

            int idx=0;
            bool f=false;

            if(n==0)
                a[0]=x;

            else
            {
                for(i=0;i<n;i++)
                {
                    if(x<=a[i])
                    {
                        idx=i;
                        f=true;
                        break;
                    }
                }

                //if f=false then x is greater than all other elements
                if(f==false)
                    a[n]=x;

                else
                {
                    for(i=n;i>idx;i--)
                        a[i]=a[i-1];

                    a[idx]=x;
                }
            }


            n++;
            print();
            cout<<endl;
        }


        int findItem(int x)
        {
            int idx=-1;
            for(i=0;i<n;i++)
            {
                if(a[i]==x)
                {
                    idx=i;
                    break;
                }
            }

            return idx;
        }

        int deleteItem(int x)
        {
            int idx=findItem(x);

            if(idx==-1)
                cout<<"Element Not Found"<<endl;
            else
            {
                for(i=idx;i<n;i++)
                    a[i]=a[i+1];

                n--;
                print();
                cout<<endl;
            }
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
    freopen("in.txt","r",stdin);
    int i,j,k;
    int x,y,z,idx;
    char ch;
    string s;
    ArrayList w;

    while(true)
    {
        getline(cin,s);
        ch=s[0];

        if(ch=='I')
        {
            x=strToNum(s);//cout<<x<<endl;
            w.insertItem(x);
        }

        else if(ch=='D')
        {
            x=strToNum(s);//cout<<x<<endl;
            w.deleteItem(x);
        }

        else if(ch=='F')
        {
            x=strToNum(s);//cout<<x<<endl;
            idx=w.findItem(x);

            if(idx==-1)
                cout<<"Not Found"<<endl;
            else
                cout<<"Found At Position "<<idx<<endl;
        }

        else
            break;
    }

    return 0;
}
