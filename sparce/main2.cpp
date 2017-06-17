#include <iostream>

using namespace std;

template<class T>
class x
{
public:
	T _x;
	x(T g){
		_x=g;
	};
	void print(){
		cout<<"hola como estas"<<endl;
	}
	~x(){};
	
};

template<class T, class C>
class este
{
public:
	C* es;
	este(T a){
		es=new C(a);
	}
	void operator () (T a){
		es->print();
	}
	~este(){};
	
};

int main(int argc, char const *argv[])
{
	este<int,x<int>> angel(4);
	angel(7);
	return 0;
}