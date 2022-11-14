#include <iostream>

int main(){

	int* A[10];

	for (int i = 0; i < 10; i++){
		int *p = new int[0];
		delete[] p;
		/* A[i] = new int[0]; */
		/* *A[i] = '*'; */
	}
	return 0;
}
