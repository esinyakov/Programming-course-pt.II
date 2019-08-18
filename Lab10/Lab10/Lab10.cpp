#include "pch.h"
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

template <class T>
class Matrixt
{
	T **a;
	int n;
	int m;
public:
	Matrixt();
	~Matrixt()
	{
		if (a != 0)
		{
			for (int i = 0; i < n; i++) delete[]a[i];
			delete a;
			cout << "destruct!" << endl;
		}
	}
	Matrixt(int nl, int ml);
	Matrixt(char* name)
	{
		int i, j;
		ifstream f1;
		f1 = ifstream(name);
		f1 >> n >> m;
		a = new T*[n];
		for (int i = 0; i < n; i++) a[i] = new T[m];
		for (i = 0; i < n; i++)
			for (j = 0; j < m; j++) f1 >> a[i][j];
		f1.close();
	}
	Matrixt(const Matrixt&);
	Matrixt operator+(Matrixt &r);

	friend ostream& operator<<(ostream &out, const Matrixt<T>& r)
	{
		for (int i = 0; i < r.n; i++)
		{
			for (int j = 0; j < r.m; j++) out << r.a[i][j] << " ";
			out << std::endl;
		}
		return out;
	}

	friend istream & operator>>(istream & in, Matrixt<T>&r)
	{
		for (int i = 0; i < r.n; i++) for (int j = 0; j < r.m; j++) in >> r.a[i][j];
		return in;
	}
};

template<class T>
Matrixt<T>::Matrixt()
{
	n = 1;
	m = 1;
	a = new T*[n];
	for (int i = 0; i < n; i++) a[i] = new T[m];
	a[0][0] = 1;
}

template<class T>
Matrixt<T>::Matrixt(int nl, int ml)
{
	n = nl;
	m = ml;
	a = new T*[n];
	for (int i = 0; i < n; i++) a[i] = new T[m];
}

template<class T>
Matrixt<T>::Matrixt(const Matrixt<T>& r)
{
	int i, j;
	n = r.n;
	m = r.m;
	a = new T*[n];
	for (i = 0; i < n; i++) a[i] = new T[m];
	for (i = 0; i < n; i++) for (j = 0; j < m; j++) a[i][j] = r.a[i][j];
}


template <class T>
Matrixt<T> Matrixt<T>::operator+(Matrixt <T> &r)
{
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) a[i][j] = a[i][j] + r.a[i][j];
	return *this;
}


int main()
{
	int n = 3;
	int m = 4;

	char catalog[] = "dat2.txt";
	Matrixt<int> a(catalog);
	cout << a << endl;

	Matrixt<int> b(n, m);
	cout << "Vvedite matrizu " << n << " na "<< m << endl;
	cin >> b;
	cout << b << endl;

	cout << "Sumarnaya matriza " << endl;
	Matrixt<int> ñ(a + b);
	cout << ñ << endl;

	Matrixt<double> da(catalog);
	cout << da << endl;

	Matrixt<double> db(n, m);
	cout << "Vvedite matrizu " << n << " na " << m << endl;
	cin >> db;
	cout << db << endl;

	cout << "Sumarnaya matriza " << endl;
	Matrixt<double> dñ(da + db);
	cout << dñ << endl;

	_getch();
	return 0;
}
