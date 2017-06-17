#include <iostream>
#include <time.h>
#include <stdio.h>

using namespace std;

template<class T>
class nodo
{
public:
	T x, y;
	T dato;
	nodo<T>* right;
	nodo<T>* down;
	nodo(T,T,T);
	~nodo(){};
	
};

template<class T>
nodo<T>::nodo(T _x, T _y, T _dato){
	dato=_dato;
	x=_x;
	y=_y;
	right=down=NULL;
}

template<class T>
class ctemp;

template <class T, T N>
class matrix
{
public:
	nodo<T>** m_hor, **m_ver;
	int dim_x, dim_y;
	matrix(int x, int y);
	bool set(T x, T y, T dato);
	T get(T x, T y);
	bool buscarx(T dato, nodo<T>**&p, T ind);
	bool buscary(T dato, nodo<T>**&p, T ind);
	bool borrar(T x, T y);
	ctemp<T> operator()(T x, T y);
	matrix<T,N> operator * (matrix<T,N> b);
	void print();
	~matrix(){};

};

template <class T, T N>
matrix<T,N>::matrix(int x, int y){
	this->dim_x=x;
	this->dim_y=y;
	m_hor=new nodo<T>*[x];
	for (int i = 0; i < x; ++i)
	{
		m_hor[i]=NULL;
	}

	m_ver=new nodo<T>*[y];
	for (int i = 0; i < y; ++i)
	{
		m_ver[i]=NULL;
	}
}

template<class T, T N>
ctemp<T> matrix<T,N>::operator()(T x, T y){
	return ctemp<T> (x,y,this);
}

template<class T, T N>
matrix<T,N> matrix<T,N>::operator * (matrix<T,N> b){
	if (this->dim_x!=b.dim_y) return matrix<T,N>(0,0);
	matrix<int,0> ab(this->dim_y,b.dim_x);
	int suma=0;
	for (int h = 0; h < this->dim_y; ++h)
	{
		for (int i = 0; i < this->dim_y; ++i)
		{
			for (int j = 0; j < this->dim_x; ++j)
			{
				suma=suma+((*this)(j,i)*b(h,j));
			}
			//cout<<"suma: "<<suma<<endl;
			ab(h,i)=suma;
			suma=0;
		}
	}

	cout<<"matriz resultado: "<<endl;
	return ab;
}

template<class T, T N>
bool matrix<T,N>::set(T x, T y, T dato){

	if(dato==0)return this->borrar(x,y);

	nodo<T>** _x, **_y;
	if(this->buscarx(y,_x,x) || this->buscary(x,_y,y)){
		(*_x)->dato=dato;
	};
	nodo<T>* n=new nodo<T>(x,y, dato);
	n->down=(*_x);
	(*_x)=n;
	n->right=(*_y);
	(*_y)=n;
	return 1;
}

template<class T, T N>
bool matrix<T,N>::buscarx(T dato, nodo<T>**&p, T ind){
	p=&(m_hor[ind]);
	//cout<<"hola"<<endl;
	while ((*p) && dato>(*p)->y){
		p = &((*p)->down);
	}

	if ((*p) && dato == (*p)->y) {
		return true;
	}
	return false;
}

template<class T, T N>
bool matrix<T,N>::buscary(T dato, nodo<T>**&p, T ind){
	p=&(m_ver[ind]);
	while ((*p) && dato>(*p)->x) {
		p = &((*p)->right);
	}

	if ((*p) && dato == (*p)->x) {
		return true;
	}
	return false;
}

template<class T, T N>
bool matrix<T,N>::borrar(T x, T y){
	nodo<T>** p;
	if (!this->buscarx(y, p, x))return 0;
	nodo<T> *t;
	t = *p;
	*p = (*p)->down;

	if (!this->buscary(x, p, y))return 0;
	t = *p;
	*p = (*p)->right;

	delete t;

	return 1;
}

template<class T, T N>
void matrix<T,N>::print(){
	nodo<T>* temp;
	temp=m_ver[1];
	while(temp!=NULL){
		//cout<<temp->dato<<endl;
		temp=temp->right;
	}
	nodo<T>* tem;
	for (int i = 0; i < dim_y; ++i)
	{
		
		tem=m_ver[i];
		for (int j = 0; j < dim_x; ++j)
		{
			if(tem!=NULL && j==tem->x && i==tem->y){
				cout<<tem->dato<<" ";
				tem=tem->right;
			}
			else{
				cout<<0<<" ";
			}
			
		}
		cout<<endl;
	}
}

template<class T, T N>
T matrix<T,N>::get(T x, T y){
		nodo<T>** temp;
		//buscarx(y,temp,x);
		if(buscarx(y,temp,x)==false){
			return 0;}
		return (*temp)->dato;
	}

template<class T>
class ctemp
{
public:
	T x, y;
	matrix<T,0>* ma;
	ctemp(T _x, T _y, matrix<T,0>* _m){
		x=_x;
		y=_y;
		ma=_m;
	}
	void operator =(T n){
		ma->set(x,y,n);
	}

	operator T(){
		return ma->get(x,y);
	}
	~ctemp(){};
};

matrix<int,0> multiplicacion(matrix<int,0> a, matrix<int,0> b){
	if (a.dim_x!=b.dim_y) return matrix<int,0>(0,0);
	matrix<int,0> ab(a.dim_y,b.dim_x);
	int suma=0;
	for (int h = 0; h < a.dim_y; ++h)
	{
		for (int i = 0; i < a.dim_y; ++i)
		{
			for (int j = 0; j < a.dim_x; ++j)
			{
				suma=suma+(a(j,i)*b(h,j));
			}
			//cout<<"suma: "<<suma<<endl;
			ab(h,i)=suma;
			suma=0;
		}
	}

	cout<<"matriz resultado: "<<endl;
	return ab;
}

int main(int argc, char const *argv[])
{
	matrix<int,0> m(4,4);

	/*m(0,0)=1;
	m(1,0)=2;
	m(2,0)=0;
	m(0,1)=2;
	m(1,1)=-1;
	m(2,1)=-1;

	n(0,0)=2;
	n(1,0)=1;
	n(2,0)=1;
	n(0,1)=-1;
	n(1,1)=1;
	n(2,1)=3;
	n(0,2)=1;
	n(1,2)=2;
	n(2,2)=4;
	cout<<"matriz: "<<endl;
	n.print();

	cout<<"actualizado: "<<endl;
	n(1,1)=5;
	n.print();
	n(1,2)=0;
	n.print();*/

	cout<<"hola"<<endl;
	m(0,0)=4;
	m(2,1)=m(0,0);
	m(1,2)=7;
	m(2,2)=3;
	m(1,1)=6;
	m(3,3)=2;
	m(2,0)=9;
	m(3,0)=8;
	cout<<"matriz: "<<endl;
	m.print();
	int a;
	a=m(2,0);
	cout<<a<<endl;
	a=m(1,1);
	cout<<a<<endl;
	cout<<"borrando con 0"<<endl;
	m(1,2)=0;
	m.print();

	cout<<"actualizado"<<endl;
	m(1,2)=m(3,3);
	m(2,1)=4;
	m.print();

	
	
	return 0;
}