#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>


using namespace std;

int min_func(int a,int b);
int intersection(int* arrayn,int* arraym,int* inter_massiv,int n,int m);

int main()
{
    srand((unsigned)time(NULL));

    int n,m,i,j;
    cout << "Enter array1 amount n: ";
    cin >>n;
    cout << "\nEnter array2 amount m: ";
    cin >>m;

    int* a;
    int* b;
    int* c;

    a = new int[n];
    b = new int[m];
    c = new int[min_func(n,m)];

    for (i=0;i<n;i++)
    {
            a[i]=rand()%10;
            cout<<a[i]<<" ";
    }
    cout<<"\n";

    for (i=0;i<m;i++)
    {
            b[i]=rand()%10;
            cout<<b[i]<<" ";
    }
    cout<<"\n";
    int k;
    k = intersection(a,b,c,n,m);

    for (i=0;i<k;i++)
    {
            cout<<c[i]<<" ";
    }
    cout<<"\n";
    delete []a;
    delete []b;
    delete []c;

    getch();
    return 0;
}

int min_func(int a,int b)
{
    if(a>b)
    {
        return b;
    }
    else
    {
        return a;
    }
}


int intersection(int* arrayn,int* arraym,int* inter_massiv,int n,int m)
{
    int k=0;
    for(int i=0; i <n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if (arrayn[i]==arraym[j])
            {
                int flag = 1;
                for(int l=0; l<k;l++)
                {
                    if(inter_massiv[l]==arrayn[i]) flag=0;
                }
                if (flag)
                {
                    inter_massiv[k++]=arrayn[i];
                }
            }
        }
    }
    return k;
}


