#include <iostream>
#include <cstdlib>




/*
*	This function should print a right triangle of stars
*
*/

int main (int argc, char * argv[]) {
//Please enter the size of the triangle you want to see!
if (argc<2)
{
	std::cout<<"./loop <number>"<<std::endl;
	return 0;
}
int i=0;
int input = std::atoi(argv[1]);
//
while (i<input) {
	for(int q=1; q<i; q++)
		std::cout<<'*';
	std::cout<<std::endl;

}

}
