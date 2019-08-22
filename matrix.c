#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef DOUBLE_NUMBERS_AFTER_POINT
#define DOUBLE_NUMBERS_AFTER_POINT 2
#endif

typedef struct Matrix Matrix;

Matrix createMatrix(int h, int w){
	Matrix matrix;
	double* contents = malloc(sizeof(double) * h * w);
	matrix.contents = contents;
	matrix.h = h;
	matrix.w = w;
	return matrix;
}

Matrix createSetMatrix(int h, int w, double *contents){
	Matrix matrix;
	matrix.contents = contents;
	matrix.h = h;
	matrix.w = w;
	return matrix;
}

Matrix createVector(int h){
	Matrix matrix;
	double* contents = malloc(sizeof(double) * h);
	matrix.contents = contents;
	matrix.h = h;
	matrix.w = 1;
	return matrix;
}

Matrix createSetVector(int h, double *contents){
	Matrix matrix;
	matrix.contents = contents;
	matrix.h = h;
	matrix.w = 1;
	return matrix;
}

void setValue(Matrix matrix, double value, int i, int j){
	matrix.contents[i * matrix.w + j] = value;
}

double getValue(Matrix matrix, int i, int j){
	return matrix.contents[i * matrix.w+ j];
}

void printVector(Matrix vector){
	int longest = 0;
	for(int i = 0; i < vector.h; i++){
		int length = lengthAsStringDouble(vector.contents[i]);
		if(length > longest){
			longest = length;
		}
	}
	for(int i = 0; i < vector.h; i++){
		int spaces = longest - lengthAsString(vector.contents[i]);
		printf("|%.2f", vector.contents[i]);
		for(int j = 0; j < spaces; j++){
			printf(" ");
		}
		printf("|\n");
	}
}

void printMatrix(Matrix matrix){
	if(matrix.w < 2){
		printVector(matrix);
		return;
	}
	int longest = 4;
	int height = matrix.h;
	int width = matrix.w;
	double *a = matrix.contents;
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			int stringlength = lengthAsStringDouble(a[i * width + j]);
			longest =  stringlength > longest ? stringlength : longest;
		}
	}
	for(int i = 0; i < height; i++){
		int spaces = (longest - lengthAsStringDouble(a[i * width]));
		printf("|");
		for(int space = 0; space < spaces; space++){
			printf(" ");
		}
		printf("%.2f    ", a[i * width]);
		for(int j = 1; j < width - 1; j++){
			spaces = (longest - lengthAsStringDouble(a[i * width + j]));
			for(int space = 0; space < spaces; space++){
				printf(" ");
			}
			printf("%.2f    ", a[i * width + j]);
		}
		spaces = (longest - lengthAsStringDouble(a[(i + 1) * width - 1]));
		for(int space = 0; space < spaces; space++){
				printf(" ");
		}
		printf("%.2f", a[(i + 1) * width - 1]);
		printf("|\n");
	}
}


void printMatrixVector(Matrix matrix, Matrix vector){
	if(matrix.w < 2){
		printVector(matrix);
		return;
	}
	int longest = 4;
	int height = matrix.h;
	int width = matrix.w;
	double *a = matrix.contents;
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			int stringlength = lengthAsStringDouble(a[i * width + j]);
			longest =  stringlength > longest ? stringlength : longest;
		}
	}
	for(int i = 0; i < height; i++){
		int spaces = (longest - lengthAsStringDouble(a[i * width]));
		printf("|");
		for(int space = 0; space < spaces; space++){
			printf(" ");
		}
		printf("%.2f    ", a[i * width]);
		for(int j = 1; j < width - 1; j++){
			spaces = (longest - lengthAsStringDouble(a[i * width + j]));
			for(int space = 0; space < spaces; space++){
				printf(" ");
			}
			printf("%.2f    ", a[i * width + j]);
		}
		spaces = (longest - lengthAsStringDouble(a[(i + 1) * width - 1]));
		for(int space = 0; space < spaces; space++){
				printf(" ");
		}
		printf("%.2f", a[(i + 1) * width - 1]);
		printf("|    %.2f\n", vector.contents[i]);
	}
}



void swapRow(Matrix matrix, int row1, int row2){
	int row1Offset = row1 * matrix.w;
	int row2Offset = row2 * matrix.w;
	for(int i = 0; i < matrix.w; i++){
		double temp = matrix.contents[row1Offset + i];
		matrix.contents[row1Offset + i] = matrix.contents[row2Offset + i];
		matrix.contents[row2Offset + i] = temp;
	}
}

void swapColumn(Matrix matrix, int column1, int column2){
	int width = matrix.w;
	for(int i = 0; i < matrix.h; i++){
		double temp = matrix.contents[i * width + column1];
		matrix.contents[i * width + column1] = matrix.contents[i * width + column2];
		matrix.contents[i * width + column2] = temp;
	}
}

void addRowToRow(Matrix matrix, int to, int add, double factor){
	int width = matrix.w;
	for(int i = 0; i < width; i++){
		matrix.contents[to * width + i] = matrix.contents[to * width + i] + factor * matrix.contents[add * width + i];
	}
}

int lengthAsStringDouble(double number){
	int num = (int)number;
	int digit = 1;
	int divider = 10;
	while(num / divider){
		divider *= 10;
		digit++;
	}
	if(number < 0){
		digit++;
	}
	return digit + DOUBLE_NUMBERS_AFTER_POINT;
}

int lengthAsString(int number){
	int digit = 1;
	int divider = 10;
	while(number / divider){
		divider *= 10;
		digit++;
	}
	if(number < 0){
		digit++;
	}
	return digit;
}


double determinant(Matrix matrix){
	if(matrix.w != matrix.h)
		return 0;
	int hw = matrix.w;
	if(hw == 1){
		return matrix.contents[0];
	}else if(hw == 2){
		return matrix.contents[0] * matrix.contents[3] - matrix.contents[1] * matrix.contents[2]; 
	}else if(hw == 3){
		return matrix.contents[0] * matrix.contents[4] * matrix.contents[8] 
		+ matrix.contents[1] * matrix.contents[5] * matrix.contents[6]
		+ matrix.contents[2] * matrix.contents[3] * matrix.contents[7]
		- matrix.contents[0] * matrix.contents[5] * matrix.contents[7]
		- matrix.contents[1] * matrix.contents[3] * matrix.contents[8]
		- matrix.contents[2] * matrix.contents[4] * matrix.contents[6];
	}else{
		double det = 0;
		for(int i = 0; i < hw; i++){
			int factor = i % 2 == 0 ? 1 : -1; 
			det += factor * matrix.contents[i] * determinant(rowRemove(columnRemove(matrix, i), 0));
		}
		return det;
	}
}

Matrix rowRemove(Matrix matrix, int row){
	Matrix result = createMatrix(matrix.h - 1, matrix.w);
	copyMatrix(matrix, result, 0, row, 0, matrix.w, 0, 0);
	copyMatrix(matrix, result, row + 1, matrix.h, 0, matrix.w, row, 0);
	return result;
}

Matrix columnRemove(Matrix matrix, int column){
	Matrix result = createMatrix(matrix.h, matrix.w - 1);
	copyMatrix(matrix, result, 0, matrix.h, 0, column, 0, 0);
	copyMatrix(matrix, result, 0, matrix.h, column + 1, matrix.w, 0, column);
	return result;
}

int copyMatrix(Matrix from, Matrix to, int heightStart, int heightEnd, int widthStart, int widthEnd, int heightOffSet, int widthOffset){
	if(widthEnd + widthOffset - widthStart > to.w || heightEnd -heightStart + heightOffSet > to.h){
		return 0;
	}
	int hs = 0;
	for(int h = heightStart; h < heightEnd; h++){
		int ws = 0;
		for(int w = widthStart; w < widthEnd; w++){
			to.contents[(heightOffSet + hs) * to.w + (ws + widthOffset)] = from.contents[h * from.w + w];
			ws++;
		}
		hs++;
	}
	return 1;
}

int symmetrical(Matrix matrix){
	for(int h = 0; h < matrix.h; h++){
		for(int w = 0; w < h; w++){
			if(matrix.contents[h * matrix.w + w] != matrix.contents[w * matrix.w + h]){
				return 0;
			}
		}
	}
	return 1;
}

int positiveDefinitQuadratic(Matrix matrix){
	if(!quadratic(matrix))
		return 0;
	int hw = matrix.w;
	for(int i = 1; i < hw; i++){
		if(determinant(rowRemove(columnRemove(matrix, i), i)) < 0)
			return 0;
	}
	return 1;
}

int quadratic(Matrix matrix){
	return matrix.w == matrix.h;
}

void cholesky(Matrix matrix, Matrix l){
	if(!quadratic(matrix))
		return;
	if(!positiveDefinitQuadratic(matrix) || ! symmetrical(matrix))
		return;
	int hw = matrix.w;
	for(int i = 0; i < hw; i++){
		for(int j = 0; j < i; j++){
			double aij = getValue(matrix, i, j);
			for(int k = 0; k < j; k++){
				aij -= getValue(l, i, k) * getValue(l, j, k);
			}
			setValue(l, (aij / getValue(l, j, j)), i, j);
		}
		double aii = getValue(matrix, i, i);
		for(int a = 0; a < i; a++){
			aii -= getValue(l, i, a) * getValue(l, i, a);
		}
		setValue(l, sqrt(aii), i, i);
	}
}