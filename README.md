# matrix-library-cpp

This is library which contains matrix class container with basic functions and operations with them

Matrix are containers representing twodimention arrays that can change in size.

This library contains two classes:

* Matrix
* SqrMatrix

## functions

### Matrix\<T>

| Function | Description |
| --- | --- |
| (constructors) | Construct matrix |
| operator= | Assign content |
| | |
| at | Return reference to element |
| operator[] | Return reference to row |
| | |
| maxSize | Return max count of rows and columns |
| rows | Return count of rows |
| cols | Return count of columns |
| getRow | Return row from matrix |
| getCol | Return column from matrix |
| empty | Test whether matrix is empty |
| rang | Calculate rang of matrix |
| | |
| resize | Change size |
| clear | Clear content |
| insertRow | Insert row into matrix |
| insertCol | Insert column into matrix |
| changeRows | Swap two rows in the matrix |
| changeCols | Swap two columns in the matrix |
| | |
| swap | Swap two matrix |
| getTransposed | Make transposed matrix and retrurn it |
| | |
| operator- | Unary: return matrix with changed sings of all elements <br> Binary: subtracting of two matrix |
| operator+ | Addition of two matrices |
| operator+= | Addition of mat |
| operator-= | Subtraction of mat |
| | |
| operator* | With matrix: multiplication of two matrix <br> With another type: multiply every element of matrix to another operand |
| operator*= | Multiply every element of matrix to operand |

### SqrMatrix\<T>

Contains all functions from basic class Matrix plus next ones

| Function | Description |
| --- | --- |
| determinant | Calculate determinant and return it |
| getInverse | Make inverse matrix and return it |
