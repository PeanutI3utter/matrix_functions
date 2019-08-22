#ifndef MATRIX_IMPLEMENTATION
#define MATRIX_IMPLEMENTATION

typedef struct Matrix
{
	double* contents;
	int h; //height
	int w; //width
} Matrix;


Matrix createMatrix(int h, int w);
Matrix createSetMatrix(int h, int w, double *contents);
Matrix createVector(int h);
Matrix createSetVector(int h, double *contents);
void setValue(Matrix matrix, double value, int i, int j);
double getValue(Matrix matrix, int i, int j);
void printMatrix(Matrix matrix);
void printMatrixVector(Matrix matrix, Matrix vector);
void printVector(Matrix vector);
int lengthAsString(int number);
int lengthAsStringDouble(double number);
void swapRow(Matrix matrix, int row1, int row2);
void addRowToRow(Matrix matrix, int to, int add, double factor);
void swapColumn(Matrix matrix, int column1, int column2);
Matrix rowRemove(Matrix matrix, int row);
Matrix columnRemove(Matrix matrix, int column);
double determinant(Matrix matrix);
int symmetrical(Matrix matrix);
int quadratic(Matrix matrix);
void cholesky(Matrix matrix, Matrix l);
int positiveDefinitQuadratic(Matrix matrix);
int copyMatrix(Matrix from, Matrix to, int heightStart, int heightEnd, int widthStart, int widthEnd, int heightOffSet, int widthOffset);

#endif
