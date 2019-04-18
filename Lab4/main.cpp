#include <iostream>
using namespace std;

#include <conio.h>
#include <math.h>

class Point
{
    double x, y;
    public:
    double rast(){return sqrt(x*x+y*y);}//расстояние до начала координат
    double rast_t( Point tl)
    {
        return sqrt((tl.get_x()-x )*( tl.get_x()-x) + (tl.get_y()-y )*( tl.get_y()-y));//расстояние между текущей точкой и входной
    }
    double get_x() {return x;}
    double get_y() {return y;}
    void set(double xv,double yv){x=xv;y=yv;}
    Point(){x=0; y=0;}
    Point(double xv, double yv){x=xv; y=yv;}
};

class Line
{
    double k,b;
    public:
    double get_k() {return k;}
    double get_b() {return b;}
    void set(double kv,double bv){k=kv;b=bv;}
    int prov(Line l)
    {
        if(l.get_k()==k){return 1;}
        else {return 0;}
    }
    Line(){k=1;b=0;}
    Line(double kv,double bv){k=kv;b=bv;}//проверка на парралельность
};

int main()
{
    int i,n;
    n = 5;
    double xc[] = {5,8,9,12,3};
    double yc[] = {12,23,2,4,5};
    double kc[] = {1,8,1,12,3};
    double bc[] = {12,23,12,4,6};
    Point* points;
    Line* lines;

    points = new Point[n];
    lines = new Line[n];
    for(i=0;i<n;i++)
    {
        points[i]=Point(xc[i],yc[i]);
        lines[i]=Line(kc[i],bc[i]);
    }

    cout<<"distance from points[0] to origin "<<points[0].rast()<<endl;
    cout<<"distance from points[0] to points[4] "<<points[0].rast_t(points[4])<<endl;
    cout<<"check if lines[0] and lines[4] are parralel:"<<endl;
    if(lines[0].prov(lines[4])){cout<<"lines are parralel";}
    else{cout<<"lines are not parralel";}

    delete[] lines;
    delete[] points;
    getch();
    return 0;
}




