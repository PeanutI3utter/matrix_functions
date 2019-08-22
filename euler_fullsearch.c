#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

int* eulerAlgFullSearch(Matrix matrix, Matrix vector);

int main(){
	Matrix matrix;
	double mc[] = {3, 4, -5, 6, 6, 5, -6, 5, 9, -4, 2, 3, 0, 2, -3, 1};
	matrix.contents = mc;
	matrix.w = 4;
	matrix.h = 4;
	Matrix vector;
	double vc[] = {39, 43, 6, 13};
	vector.contents = vc;
	vector.h = 4;
	vector.w = 1;
	eulerAlgFullSearch(matrix, vector);
	printf("\n");
	printf("\n");
	return 0;
}

int* eulerAlgFullSearch(Matrix matrix, Matrix vector){
	int height = matrix.h;
	int width = matrix.w;
	printMatrixVector(matrix, vector);
	printf("\n\n\n");
	Matrix resultVector = createVector(height);
	Matrix x = createVector(height);
	for(int i = 0; i < height; i++){
		x.contents[i] = i;
	} 
	for(int a = 0; a < height; a++){
		int highestElementRow = a;
		int highestElementColumn = a;
		double highestElement = fabs(matrix.contents[highestElementRow * width + highestElementColumn]);
		for(int i = a; i < height; i++){
			for(int j = a; j < width; j++){
				double element = fabs(matrix.contents[i * width + j]);
				if(element > highestElement){
					highestElementRow = i;
					highestElementColumn = j;
					highestElement = element;
				}
			}
		}
		if(a != highestElementRow){
			printf("swap %d row with %d row:\n\n", a, highestElementRow);
			swapRow(matrix, a, highestElementRow);
			swapRow(vector, a, highestElementRow);
			printMatrixVector(matrix, vector);
			printf("\n\n\n");
		}
		if(a != highestElementColumn){
			printf("swap %d column with %d column:\n\n", a, highestElementColumn);
			swapColumn(matrix, a, highestElementColumn);
			swapRow(x, a, highestElementColumn);
			printMatrixVector(matrix, vector);
			printf("\n\n\n");
		}
		double dominant = matrix.contents[a * width + a];
		for(int row = a + 1; row < height; row++){
			float factor = (matrix.contents[row * width + a] / dominant) * -1;
			printf("add %f * row %d to row %d\n", factor, a, row);
			addRowToRow(matrix, row, a, factor);
			addRowToRow(vector, row, a, factor);
		}
		printf("\n\n\n");
		printMatrixVector(matrix, vector);
		printf("\n\n\n");
		printf("\n\n\n");
		for(int i = height - 1; i >= 0; i--){
			int xNum = x.contents[i];
			double tempRes = vector.contents[i];
			for(int j = i + 1; j < height; j++){
				int jj = x.contents[j];
				tempRes = tempRes - matrix.contents[i * height + j] * resultVector.contents[jj];
			}
			resultVector.contents[xNum] = tempRes / matrix.contents[i * width + i];
		}
	}
	printf("permutation matrix:\n");
	printMatrix(x);
	printf("\n\nresult:\n\n");
	printMatrix(resultVector);
}
