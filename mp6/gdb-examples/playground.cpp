#include <iostream>
using namespace std;



// pbv
void fooval(int x) {
	x = x * 2;
	
}
// pbp
void fooval(int * x) {
	*x = *x * 2;
}

// pbr
void fooval1(int & x) {
	x = x * 2;
}
// pbp
void bar(int * z) {
	cout<<" address of z: "<<&z<<endl;

	cout<<"z: "<<z<<endl;
	z = new int(5);
	cout<<"z: "<<z<<endl;
}

// pbpbp
void bar2(int  *  &z) {
	int x=5;
	z = &x;
	
}

// pbr pointer

int main () {
	int *q =NULL;

	cout<<*q<<endl;
	// int x=10;	

	// cout<<"x: "<<x<<endl;

	// fooval(&x);

	// cout<<"x: "<<x<<endl;

	// fooval1(x);

	// cout<<"x: "<<x<<endl;
	int * y=(int *)10;


	cout<<"y: "<<y<<endl;

	bar2(y);

	cout<<"y: "<<y<<endl;


	delete y;

}





