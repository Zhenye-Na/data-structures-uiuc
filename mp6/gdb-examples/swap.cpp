#include <iostream>
#include <cstdlib>


/*
*	This function should swap the input values
*
*/


int main (int argc, char * argv[]) {
//Please enter the numbers you want to swap
if (argc<3)
{
	std::cout<<"./swap num1 num2"<<std::endl;
	return 0;
}
int i=0;
int a = std::atoi(argv[1]);
int b = std::atoi(argv[2]);

a=b;
b=a;

std::cout<<"A: "<<a<<" B: "<<a<<std::endl;

}
