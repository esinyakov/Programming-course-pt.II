#include "pch.h"
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

class Array
{
	int* ptr;//ukazatel na massiv
	int size;//razmer massiva
public:
	Array();
	Array(int);
	Array(const Array&);//konstructor kopii
	~Array();
	int getSize();//vozvratit kol-vo elementov massiva
	Array operator=(const Array&);//prisvaivanie
	bool operator== (const Array&);//sravnenie
	int& operator[] (int);//peregruzka na vihod za predeli massiva
	Array operator+ (const Array&);//slozhenie massivov
	Array operator+= (int);//dobavlenie elementov v konec massiva
	int search(const int);//poisk v massive po kluchu
	Array operator& (const Array& rt);//peresechenie
	friend ostream &operator<<(ostream &, const Array &);
	friend istream &operator>>(istream &, const Array &);
	void setfile(char* name);
};

int min(int a, int b)
{
	if (a > b) return b;
	else return a;
}

int max(int a, int b)
{
	if (a > b) return a;
	else return b;
}

Array::Array()
{
	cout << "constructor Array()" << endl;
	size = 0;
	ptr = 0;
}

Array::Array(int n)
{
	size = n;
	ptr = new int[size];
	for (int i = 0; i < size; i++) ptr[i] = 0;
	cout << "constructor Array(int n)" << endl;
}


Array::Array(const Array& arr)//konstntnaia ssilka garantiruet chto argument ne izmenitsa
{
	size = arr.size;
	ptr = new int[size];
	for (int i = 0; i < size; i++) ptr[i] = arr.ptr[i];
}

Array Array::operator=(const Array& rt)
{
	if (&rt == this)
		return *this;
	if (ptr != 0) delete[]ptr;
	size = rt.size;
	ptr = new int[size];
	for (int i = 0; i < size; i++) ptr[i] = rt.ptr[i];
	return *this;//razimenovammi ukazatel na tekuchi obekt
}

Array::~Array()
{
	if (ptr != 0 && size > 0)
	{
		delete[]ptr;
		ptr = 0;
		size = 0;
	}
}

void Array::setfile(char* name)
{
	int k, n, i;
	ifstream f1;
	f1 = ifstream(name);
	f1 >> n;
	size = n;
	ptr = new int[n];
	for (i = 0; i < n; i++) f1 >> ptr[i];
	f1.close();
}

int& Array::operator[] (int i)//vozvrashaem po ssilke inache kak vidim na stroke 130 budet oshibka
{
	if (i < 0 || i >= size)
	{
		cout << "\n Oshibka indeksa " << i << endl;
		//exit(1);
	}
	else return *(ptr + i);//vosvrat elementa
}

bool Array::operator== (const Array& rt)
{
	if (size != rt.size) return false;//massivi s raznim kolich elementov
	for (int i = 0; i < size; i++)
		if (ptr[i] != rt.ptr[i]) return false;//massivi ne ravni
	return true;
}

Array Array::operator+ (const Array& rt)
{

	Array r(max(size, rt.size));
	for (int i = 0; i < min(size, rt.size); i++)
		r.ptr[i] = ptr[i] + rt.ptr[i];
	return r;
}

int Array::search(const int key)//poisk po kluchu
{
	for (int i = 0; i < size; i++)
		if (key == ptr[i]) return(i);
	return -1;
}

Array Array::operator& (const Array& rt)
{
	int i, j;
	if (size > rt.size) size = rt.size;
	Array r(size);
	for (i = 0, j = 0; i < size; i++)
		if (search(rt.ptr[i]) != -1) r.ptr[j++] = rt.ptr[i];
	Array rez(j);
	for (i = 0; i < j; i++) rez[i] = r.ptr[i];
	delete[] r.ptr;
	return rez;
}

int Array::getSize() { return size; }//vozvrazhaem kol-vo elem massiva

Array Array::operator+= (int el)
{
	Array result(size);
	result = *this;
	delete[] ptr;
	size = size + 1;
	ptr = new int[size];
	for (int i = 0; i < (size - 1); i++) ptr[i] = result.ptr[i];
	ptr[size - 1] = el;
	return *this;
}

//peregruzhennie operatori izvlechenia iz potoka >> i zapisi
//v potok << obyavlautsa kak druzhestvennie funkcii klassa
//dla obrashenia k zakritim polam, naprimer k ptr i k size

ostream& operator<< (ostream& out, const Array& b)//vivod elementov massiva na ekran
{
	for (int i = 0; i < b.size; i++) out << " " << b.ptr[i];
	out << endl;
	return out;//<<" "<<,<<" " - vosvrachaet object ostream kotori popadaet v sleduychi <<, poetomu
}//peregruzka vozvrachaet object ostream

//Samoe interesnoe sdes - tip vozvrata, s peregruzkoi ariphimiticheskih operatorov mi
//vichislali i vozvrashali resultat po znacheniu. Odnako esli vozvratit std::ostream to
//poluchitsa oshibka compilatora, eto sluchitsa iz za togo chto std::ostream 
//zapreshaet svoe kopirovanie

istream& operator>> (istream& in, const Array& b)//vvod elementov c klaviaturi
{
	for (int i = 0; i < b.size; i++) in >> b.ptr[i];
	return in;//>>" ">>,>>" " - vosvrachaet object istream kotori popadaet v sleduychi >>, poetomu
}//peregruzka vozvrachaet object istream

int main()
{
	char catalog[] = "dat1.txt";
	int i, n;
	bool par;
	Array *a, *b;
	Array ar1, ar2, ar3, ar, ar4;
	n = 3;
	cout << "Schtinanni iz faila massiv ar4" << endl;
	ar4.setfile(catalog);
	cout << ar4;
	ar1 = Array(n);
	cout << "Vvedite " << n << " elementa massiva ar1 cherez probel" << endl;
	cin >> ar1;
	cout << "Vivod ar1 v zikle" << endl;
	for (i = 0; i < ar1.getSize(); i++) cout << ar1[i] << " " << endl;
	cout << "Obrachenie k nesuchestv elementu ar1" << endl;
	cout << ar1[1000] << " " << endl;//peregruzka[]
	cout << "Vivod ar1 s pomochui peregruzki" << endl;
	cout << ar1;
	ar2 = Array(ar1);//konstruktor kotori kopiruet vhodachii massiv,peregruzka operatora prisvaivanie
	cout << "ar2=Array(ar1), vivod ar2" << endl;
	cout << ar2;
	par = ar1 == ar4;//peregruzka sravnenia
	cout << "sravnenie ar1 i ar4 " << par << endl;
	ar3 = ar2 + ar1;//poelemntoe skladivanie ottalkivayas ot menshego massiva
	ar = ar3;
	cout << "ar3=ar2+ar1,ar=ar3 vivod ar" << endl;
	cout << ar;
	cout << "vivod ar3" << endl;
	cout << ar3;
	cout << "ar1+=9 vivod ar1 " << endl;//peregruzka dobavlenie v konec
	ar1 += 9;
	cout << ar1;
	_getch();
	return 0;
}