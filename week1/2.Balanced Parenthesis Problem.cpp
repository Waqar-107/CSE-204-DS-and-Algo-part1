/*Balanced Parenthesis Problem*/
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


        delete a;
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

            a[n]=x;n++;
        }


        int deleteItem()
        {
            //only one element in the list and waiting to insert another at position 1
            if(n>0)
            {
                n--;
                return a[n];
            }

            return -1;
        }

        void clearList()
        {
            n=0;
            cout<<"Clear Completed"<<endl;
        }

        int SIZE()
        {
            return n;
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


int main()
{
    int i,j,k;
    string s;
    char ch;
    ArrayList w;

    cin>>s;
    int len=strlen(s);
    bool f=true;

    for(i=0;i<len;i++)
    {
        if(s[i]=='(' || s[i]=='{' || s[i]=='[')
            w.insertItem(s[i]);

        else
        {
            ch=w.deleteItem();

            if(s[i]==')' && ch=='(')
                continue;

            else if(s[i]=='}' && ch=='{')
                continue;

            else if(s[i]==']' && ch=='[')
                continue;

            else
            {
                f=false;break;
            }
        }
    }

    if(w.SIZE()!=0)
        f=false;

    if(f)
        cout<<"Balanced"<<endl;
    else
        cout<<"Not Balanced"<<endl;

    w.clearList();

    return 0;
}
