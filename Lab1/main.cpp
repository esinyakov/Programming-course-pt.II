#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>


using namespace std;

int main()
{
    srand((unsigned)time(NULL));

    int n,m,i,j;
    cout << "Enter array string number n: ";
    cin >>n;
    cout << "\nEnter array column number m: ";
    cin >>m;

    int** a;
    int* b;

    a = new int*[n];
    b = new int[n];

    for(i=0;i<n;i++)
    {
        *(a+i)=new int[m];
    }

    for (i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            a[i][j]=rand()%100;
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }

    cout<<"\n";;

    int min;
    for(i=0;i<n;i++)
    {
        min = a[i][0];
        for(j=0;j<m;j++)
        {
            if (a[i][j]<min) min = a[i][j];
        }
        b[i] = min;
    }

    int tmp;
    int* tmp_pa;

    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if (b[j]>b[j+1])
            {
                tmp=b[j+1];
                b[j+1]=b[j];
                b[j]=tmp;

                tmp_pa=*(a+j+1);
                *(a+j+1)=*(a+j);
                *(a+j)=tmp_pa;
            }
        }
    }

    for (i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }

    for (i=0;i<n;i++)
    {
        delete []a[i];
    }
    delete []a;
    delete []b;

    getch();
    return 0;
}
