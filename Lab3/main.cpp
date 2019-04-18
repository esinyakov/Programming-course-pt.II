#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>

using namespace std;

struct point
{
    double x,y;
};

struct line
{
    double k,b;
};

double rast(point &t1, point &t2);
point lines_point(line &l1,line &l2);
point** matr_lines_point(line* z,int n);
double** matr_rast(point* z,int n);

int main()
{
    const int n =5;

    struct point points[n];
    struct line lines[n];

    srand((unsigned)time(NULL));
    int i,j;
    for (i=0;i<5;i++)
    {
        points[i].x = rand()%5;
        points[i].y = rand()%5;
        cout<<"point"<<i<<" x="<<points[i].x<<" y="<<points[i].y<<endl;
        lines[i].k = rand()%5;
        lines[i].b = rand()%5;
        cout<<"line"<<i<<" k="<<lines[i].k<<" b="<<lines[i].b<<endl;
    }

    double** matrrast = matr_rast(points,n);
    point** matrlinespoints = matr_lines_point(lines,n);


    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
        {
            cout<<"point"<<i<<" and point"<<j<<" rast ="<<matrrast[i][j]<<endl;
        }

    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
        {
            cout<<"line"<<i<<" and line"<<j<<" cross point: x= "<<matrlinespoints[i][j].x<<" y="<<matrlinespoints[i][j].y<<endl;
        }

    cout<<"case of inf or nan lines have no cross point"<<endl;

    getch();
    return 0;
}

double rast(point &t1, point &t2)
{
    return sqrt((t1.x-t2.x)*(t1.x-t2.x)+(t1.y-t2.y)*(t1.y-t2.y));
}

point lines_point(line &l1,line &l2)
{
    point t;
    t.x=(l2.b-l1.b)/(l1.k-l2.k);
    t.y=l1.k*t.x+l1.b;

    return t;
}

point** matr_lines_point(line* z,int n)
{
    point** a;
    int i,j;
    a = new point* [n];

    for(i=0;i<n;i++)
        a[i]=new point[n];

    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            a[i][j]=lines_point(z[i],z[j]);

    return a;
}

double** matr_rast(point* z,int n)
{
    double** a;
    int i,j;
    a = new double* [n];

    for(i=0;i<n;i++)
        a[i]=new double[n];

    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            a[i][j]=rast(z[i],z[j]);

    return a;
}
