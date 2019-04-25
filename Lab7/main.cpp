#include <iostream>
using namespace std;

#include <math.h>

typedef double (*fun)(double x);
double f1(double x){return sin(x);}
double f2(double x){return cos(x);}
fun fc[]={f1,f2};//budem nahodit integral etih funkcii

class Baza_Integ_virt
{
    public:
    virtual double integral()=0;
    virtual float get_a()=0;
    virtual float get_b()=0;
    Baza_Integ_virt(){}
    virtual ~Baza_Integ_virt(){}
};

class Int_trap_virt: public Baza_Integ_virt
{
    protected:
    double a,b;
    fun f;
    long int n;
    public:
    Int_trap_virt():Baza_Integ_virt(){}
    Int_trap_virt(double av,double bv,fun ff):Baza_Integ_virt(){a=av;b=bv;f=ff;n=200;}
    float get_a(){return a;}
    float get_b(){return b;}
    double integral()
    {
        double s,h,y,x;
        long int i;
        for(h=(b-a)/n,s=(f(a)+f(b))*h/2,i=1,x=a;i<n-1;i++)
        {
            x+=h;
            s+=(f(x)*h);
        }
        return s;
    }

    ~Int_trap_virt(){cout<<"Destructor int trap virt";};

};

class Int_parab_virt: public Baza_Integ_virt
{
    protected:
    double a,b;
    fun f;
    long int n;
    public:
    Int_parab_virt():Baza_Integ_virt(){}
    Int_parab_virt(double av,double bv,fun ff):Baza_Integ_virt(){a=av;b=bv;f=ff;n=200;}
    float get_a(){return a;}
    float get_b(){return b;}
    double integral()
    {
        double s,h,y,x;
        long int i;
        for(h=(b-a)/n,s=(f(a)+f(b))*(h/3),i=1,x=a;i<n-1;i++)
        {
            x+=h;
            if(i%2) s+=(2*f(x)*(h/3));
            else s+=(4*f(x)*(h/3));
        }
        return s;
    }
    ~Int_parab_virt(){cout<<"Destructor int parab virt";}

};

int main()
{
    double a(0),b(3.14);

    Baza_Integ_virt* array_pbaza[2];

    array_pbaza[0]= new Int_trap_virt(a,b,fc[0]);
    array_pbaza[1]= new Int_parab_virt(a,b,fc[0]);

    cout<<"x1="<<a<<" x2="<<b<<" integral trap method sin= "<<array_pbaza[0]->integral()<<endl;
    cout<<"x1="<<a<<" x2="<<b<<" integral parab method sin= "<<array_pbaza[1]->integral()<<endl;

    return 0;
}
