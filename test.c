#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(){	
	/*
	Matrix matrix;
	double mc[] = {3, 4, -5, 6, 6, 5, -6, 5, 9, -4, 2, 3, 0, 2, -3, 1};
	matrix.contents = mc;
	matrix.w = 4;
	matrix.h = 4;
	*/
	Matrix matrix;
	double mc[] = {2, 4, 0, -3, 5, 1, 5, 0, 3, 1, -2, 1, 2, 0, 3, 0, 0, -1, 3, 4, 5, 6, 0, -15, 0};
	matrix.contents = mc;
	matrix.w = 5;
	matrix.h = 5;
	double mc2[] = {9, 3, -6, 12, 3, 26, -7, -11, -6, -7, 9, 7, 12, -11, 7, 60};
	Matrix fourfour = createSetMatrix(4, 4, mc2);
	double symmetry[] = {1, 2, 1, 2, 5, 4, 1, 4, 14}; 
	Matrix symmetricalMatrix = createSetMatrix(3, 3, symmetry);
	Matrix choleskyOfFourfour = createMatrix(4,4);
	printMatrix(fourfour);
	char *sym = symmetrical(fourfour) ? "yes" : "no";
	printf("symmetrical : %s\n", sym);
	char *posDef1 = positiveDefinitQuadratic(fourfour) ? "yes" : "no";
	printf("positive definite : %s\n\n\n", posDef1);
	cholesky(fourfour, choleskyOfFourfour);
	printMatrix(choleskyOfFourfour);
	printf("\n\n\n\n");
	char *sym1 = symmetrical(symmetricalMatrix) ? "yes" : "no";
	printMatrix(symmetricalMatrix);
	printf("symmetrical : %s\n", sym1);
	char *posDef = positiveDefinitQuadratic(symmetricalMatrix) ? "yes" : "no";
	printf("positive definite : %s\n\n\n\n", posDef);
	Matrix chomskyOfSym = createMatrix(3, 3);
	cholesky(symmetricalMatrix, chomskyOfSym);
	printMatrix(chomskyOfSym);
	return 0;
}