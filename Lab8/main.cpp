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
    Point* p_in;//massiv intervalov po osi x, gde x nachalo intervala,y konecintervala
    int kol_in;//kolichestvo intervalov
    protected:
    Point* p;//massiv tochek tabulirovannoi funkcii
    int n;
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

    ~Baza_tab(){cout<<"Baza_tab destructor is called"<<endl; Destroy();}
};

class Baza_poisk_virt
{
    public:
    Baza_poisk_virt(){}
    virtual double poisk(double eps)=0;
    virtual double get_a()=0;
    virtual int get_n()=0;
    virtual ~Baza_poisk_virt(){}
};

class Met_xord_virt: public Baza_poisk_virt
{
    protected:
    double a,b;
    fun f;
    int n;
    public:
    double poisk(double eps)
    {
        double d,xt,xp,fa,fb,fx;
        fa=f(a);
        fb=f(b);
        xp=a - fa*((b - a)/(fb - fa));
        d=1; n=1;
        fx=f(xp);
        while(fabs(fx) > eps && fabs(d) > eps && n < 55360)
        {
            if(fa*fx < 0)
            {
                b=xp;
                fb=fx;
            }
            else
            {
                a=xp;
                fa=fx;
            }
            xt=a - fa*((b - a)/(fb - fa));
            fx=f(xt);
            d=xt - xp;
            xp=xt;
            n++;
        }
        return xp;
    }
    int get_n(){return n;}
    double get_a(){return a;}
    Met_xord_virt(){}
    Met_xord_virt(double av,double bv,fun ff):Baza_poisk_virt(){a=av;b=bv;f=ff;}
    ~Met_xord_virt(){}
};

class Met_newton_virt: public Baza_poisk_virt
{
    protected:
    double a,b; fun f; int n;
    public:
    double poisk(double eps)
    {
        double xp,xt,d,h,fp,pfa,pfb;
        int i;
        h=0.1e-11;
        xp=a;
        d=1; n=0;
        while(fabs(d) > eps && n < 100)
        {
            fp=(f(xp+h)-f(xp))/h;
            if(fabs(fp)>0.1e-11)
                xt = xp - f(xp)/fp;
            else break;
            n++;
            d=(xt-xp);
            xp=xt;
        }
        return xt;
    }
    int get_n(){return n;}
    double get_a(){return a;}
    Met_newton_virt(){}
    Met_newton_virt(double av,double bv,fun ff):Baza_poisk_virt(){a=av;b=bv;f=ff;}
    ~Met_newton_virt(){}
};
int main()
{
    Point* p;//dla intrevalov nulei
    Point* tw; //tw dla tabulacii
    double a(2),b(4);
    int i,j,n(20),m(2);

    Baza_tab v(a,b,n);
    Baza_poisk_virt* array_pbaza_virt[2];//massiv ukasatelei na bazovi abstracnti class


    tw=v.tabul(fc[0]);
    for(j=0;j<v.get_n();j++)
    {
        cout<<"point"<<j<<" x="<<tw[j].get_x()<<" y="<<tw[j].get_y()<<endl;
    }

    Met_xord_virt mxv(a,b,fc[0]);
    Met_newton_virt mnv(a,b,fc[0]);
    array_pbaza_virt[0] = &mxv;//napravili ukazatel na object metod xord
    array_pbaza_virt[1] = &mnv;//napravili ukazatel na object metod newtona

    p=v.interval_nul();
    for(j=0;j<v.get_kol_in();j++)
    {
        cout<<"interval"<<j<<" x1="<<p[j].get_x()<<" x2="<<p[j].get_y()<<endl;
        cout<<"equation root Newton method= "<<array_pbaza_virt[0]->poisk(0.01)<<endl;//dinamicheski polimorphizm
        cout<<"equation root Chord method= "<<array_pbaza_virt[1]->poisk(0.01)<<endl;//dinamicheski polimorphizm
    }

    getch();
    return 0;
}
