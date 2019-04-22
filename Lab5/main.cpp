#include <iostream>
using namespace std;

#include <conio.h>
#include <math.h>

class Point
{
    double x, y;
    public:
    double rast(){return sqrt(x*x+y*y);}
    double rast_t( Point tl)
    {
        return sqrt((tl.get_x()-x )*( tl.get_x()-x) + (tl.get_y()-y )*( tl.get_y()-y));
    }
    double get_x() {return x;}
    double get_y() {return y;}
    void set(double xv,double yv){x=xv;y=yv;}
    Point(){x=0; y=0;}
    Point(double xv, double yv){x=xv; y=yv;}
};

typedef double (*fun)(double x);
double f1(double x){return sin(x);}
double f2(double x){return cos(x);}
fun fc[]={f1,f2};//massiv funkcii kotorii mi budem tabilurovat

class Baza_tab
{
    double a,b;
    int n;
    Point* p;//massiv tochek tabulirovannoi funkcii
    Point* p_in;//massiv intervalov po osi x, gde x nachalo intervala,y konecintervala
    int kol_in;//kolichestvo intervalov
    public:
    int get_n(){return n;}
    int get_kol_in(){return kol_in;}
    double get_a(){return a;}
    double get_b(){return b;}

    Point* tabul(fun f)//metod tabulyacii, vosvrachaet massiv tochek vhodnoi funckii
    {
        double x,h,y; int i;
        for(i=0,h=(b-a)/n,x=a;i<n;i++)
        {
            y = f(x);
            p[i]=Point(x,y);
            x+=h;
        }
        return p;
    }

    Point* interval_nul()
    {
        int i,j;
        Point* dt;//vremenni massiv t.k nam ne nado stolko mesta
        dt = new Point[n];
        for(i=0,j=0;i<n-2;i++)
            if(p[i].get_y()*p[i+1].get_y()<0)
            {
                dt[j]=Point(p[i].get_x(),p[i+1].get_x());
                j++;
            }

        p_in = new Point[j];
        for (i=0;i<j;i++) p_in[i]=dt[i];
        delete[] dt;
        kol_in = j;
        return p_in;
    }

    void Destroy()
    {
        if(n>0){delete[]p;n=0;}
        if(kol_in>0){delete[] p_in; kol_in=0;}
    }

    Baza_tab(){a=0;b=0;n=0;kol_in=0;}
    Baza_tab(double av,double bv,int nv)
    {
        a=av;
        b=bv;
        n=nv;
        p=new Point[n];
        kol_in=0;
    }

    ~Baza_tab(){cout<<"destructor is called"<<endl; Destroy();}
};

int main()
{
    Point* p;//dla lokalnih ekstremumov
    Point* tw; //tw dla tabulacii
    double a(0),b(10);
    int i,j,n(20),m(2);

    Baza_tab v(a,b,n);

    for(i=0;i<m;i++)
    {
        tw=v.tabul(fc[i]);
        for(j=0;j<v.get_n();j++)
        {
            cout<<"point"<<j<<" x="<<tw[j].get_x()<<" y="<<tw[j].get_y()<<endl;
        }
        p=v.interval_nul();
        for(j=0;j<v.get_kol_in();j++)
        {
            cout<<"interval"<<j<<" x1="<<p[j].get_x()<<" x2="<<p[j].get_y()<<endl;
        }
    }

    getch();
    return 0;
}
