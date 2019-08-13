#include "Matrix.h"

template<typename T>
Matrix<T>::Matrix(const size_t rows, const size_t cols, const T &value)
	: m_rows{ rows }, m_cols{ cols }
{
	//If dimension is wrong throw exception
	if (m_rows > maxSize() || m_cols > maxSize())
		throw std::out_of_range("Wrong dimensions");

	//Resize matrix 
	m_data.resize(m_rows);
	for (auto &row : m_data)
		row.resize(m_cols);

	//Filling by value
	for (auto &row : m_data)
		for (auto &el : row)
			el = value;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &mat) 
	: m_rows{ mat.m_rows }, m_cols{ mat.m_cols } 
{
	//Resize matrix
	m_data.resize(m_rows);
	for (auto &row : m_data)
		row.resize(m_cols);

	//Copying data of matrix
	for (size_t i{ 0 }; i < m_rows; i++)
		for (size_t j{ 0 }; j < m_cols; j++)
			m_data[i][j] = mat.m_data[i][j];
}

template<typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>> &list)
	: m_rows{ list.size() }, m_cols{ list.begin()->size() }
{
	//If dimension is wrong throw exception
	if (m_rows > maxSize() || m_cols > maxSize())
		throw std::out_of_range("Wrong dimensions");

	//Resize matrix
	m_data.resize(m_rows);
	for (auto &row : m_data)
		row.resize(m_cols);

	//Copying data of initializer list to data
	size_t curRow{ 0 };
	for (const auto &listRow : list)
	{
		if (listRow.size() != m_cols)
			throw std::out_of_range("Wrong dimensions");

		size_t curCol{ 0 };
		for (const auto &listEl : listRow)
		{
			m_data[curRow][curCol] = listEl;
			++curCol;
		}
		++curRow;
	}
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &mat) 
{
	if (this == &mat)
		return *this;

	m_rows = mat.m_rows;
	m_cols = mat.m_cols;
	m_data.clear();

	//Resize matrix
	m_data.resize(m_rows);
	for (auto &row : m_data)
		row.resize(m_cols);

	//Copying data of matrix
	for (size_t i{ 0 }; i < m_rows; i++)
		for (size_t j{ 0 }; j < m_cols; j++)
			m_data[i][j] = mat.m_data[i][j];

	return *this;
}

template<typename T>
T& Matrix<T>::at(const size_t row, const size_t col)
{
	//If dimension is wrong throw exception
	if (row >= m_rows || col >= m_cols)
		throw std::out_of_range("Wrong dimensions");

	return m_data[row][col];
}

template<typename T>
const T& Matrix<T>::at(const size_t row, const size_t col) const
{
	//If dimension is wrong throw exception
	if (row >= m_rows || col >= m_cols)
		throw std::out_of_range("Wrong dimensions");

	return m_data[row][col];
}

template<typename T>
std::vector<T>& Matrix<T>::operator[](const size_t row)
{
	//If dimension is wrong throw exception
	if (row >= m_rows)
		throw std::out_of_range("Wrong dimensions");

	//return row of matrix
	return m_data[row];
}

template<typename T>
const std::vector<T>& Matrix<T>::operator[](const size_t row) const
{
	//If dimension is wrong throw exception
	if (row >= m_rows)
		throw std::out_of_range("Wrong dimensions");

	//return row of matrix
	return m_data[row];
}

template<typename T>
std::vector<T> Matrix<T>::getRow(size_t rowId) const
{
	//If dimension is wrong throw exception
	if (rowId >= m_rows)
		throw std::out_of_range("Wrong dimensions");

	//Copy row and return
	std::vector<T> row{ m_data[rowId] };
	return row;
}

template<typename T>
std::vector<T> Matrix<T>::getCol(size_t colId) const
{
	//If dimension is wrong throw exception
	if (colId >= m_cols)
		throw std::out_of_range("Wrong dimensions");

	//Copy column and return
	std::vector<T> col;
	for (size_t i{ 0 }; i < m_rows; ++i)
		col.push_back(m_data[i][colId]);

	return col;
}

template<typename T>
size_t Matrix<T>::rang() const
{
	size_t res{ 0 };
	//It shows which rows and columns was chosen for creating minor.
	std::vector<int8_t> chosenRows(m_rows, 0);
	std::vector<int8_t> chosenCols(m_cols, 0);
	//Count of all chosen rows and columns.
	size_t cntChosenRows{ 0 };
	size_t cntChosenCols{ 0 };
	//Id of previous chosen row and column. Need to delite if minor equal zero.
	size_t prevChosenRow{ 0 };
	size_t prevChosenCol{ 0 };

	while (res < m_rows && res < m_cols)
	{
		SqrMatrix<T> minor{ res + 1 };
		size_t minorRow{ 0 };

		for (size_t i{ 0 }; i < m_rows; ++i)
		{
			//Check if need to choose one more row
			if (chosenRows[i] == -1)
				continue;
			if (chosenRows[i] == 0)
				if (cntChosenRows == minor.m_rows)
					continue;
				else
				{
					++cntChosenRows;
					chosenRows[i] = 1;
					prevChosenRow = i;
				}

			size_t minorCol{ 0 };
			for (size_t j{ 0 }; j < m_cols; ++j)
			{
				//Check if need to choose one more row
				if (chosenCols[j] == -1)
					continue;
				if (chosenCols[j] == 0)
					if (cntChosenCols == minor.m_cols)
						continue;
					else
					{
						++cntChosenCols;
						chosenCols[j] = 1;
						prevChosenCol = j;
					}
				
				//filling minor
				minor[minorRow][minorCol] = m_data[i][j];
				++minorCol;
			}
			++minorRow;
		}

		T minorDet = minor.determinant();
		if (minorDet != T(0))
		{
			++res;
			for (size_t i{ 0 }; i < chosenRows.size(); ++i)
				if (chosenRows[i] == -1)
					chosenRows[i] = 0;
			for (size_t i{ 0 }; i < chosenCols.size(); ++i)
				if (chosenCols[i] == -1)
					chosenCols[i] = 0;
		}
		//If In matrix no more not zero minors we return rang.
		else if (std::find(chosenRows.begin(), chosenRows.end(), 0) == chosenRows.end() && std::find(chosenCols.begin(), chosenCols.end(), 0) == chosenCols.end())
			return res;
		else
		{
			--cntChosenCols;
			chosenCols[prevChosenCol] = -1;
			//if In matrix no more not chosen colums we restart all chosings in columns and continue with new row.
			if (std::find(chosenCols.begin(), chosenCols.end(), 0) == chosenCols.end())
			{
				for (size_t i{ 0 }; i < chosenCols.size(); ++i)
					if (chosenCols[i] == -1)
						chosenCols[i] = 0;
				--cntChosenRows;
				chosenRows[prevChosenRow] = -1;
			}
		}
	}

	return res;
}

template<typename T>
void Matrix<T>::resize(const size_t rows, const size_t cols, const T &value)
{
	//If dimension is wrong throw exception
	if (rows > maxSize() || cols > maxSize())
		throw std::out_of_range("Wrong dimensions");

	//If one of new dimensions equal zero matrix become empty
	if (rows == 0 || cols == 0)
	{
		m_data.clear();
		m_rows = 0;
		m_cols = 0;
		return;
	}

	//Change count of rows
	if (rows != m_rows)
	{
		m_data.resize(rows, std::vector<T>(m_cols, value));
		m_rows = rows;
	}

	//Change count of cols
	if (cols != m_cols)
	{
		for (size_t i{ 0 }; i < m_rows; ++i)
			m_data[i].resize(cols, value);
		m_cols = cols;
	}
}

template<typename T>
void Matrix<T>::clear()
{
	m_rows = 0;
	m_cols = 0;
	m_data.clear();
}

template<typename T>
void Matrix<T>::insertRow(const size_t rowId, const std::vector<T> &row)
{
	//If dimension is wrong throw exception
	if (row.size() != m_cols || rowId >= m_rows)
		throw std::out_of_range("Wrong dimensions");
	
	//Change row in matrix
	m_data[rowId] = row;
}

template<typename T>
void Matrix<T>::insertCol(const size_t colId, const std::vector<T>& col)
{
	//If dimension is wrong throw exception
	if (col.size() != m_rows || colId >= m_cols)
		throw std::out_of_range("Wrong dimensions");

	//Change column in matrix
	for (size_t i{ 0 }; i < m_rows; ++i)
		m_data[i][colId] = col[i];
}

template<typename T>
void Matrix<T>::changeRows(const size_t row1Id, const size_t row2Id)
{
	//If dimension is wrong throw exception
	if (row1Id >= m_rows || row2Id >= m_rows)
		throw std::out_of_range("Wrong dimensions");

	//If they are same rows don't change them
	if (row1Id == row2Id)
		return;

	//Change rows
	std::vector<T> temp{ m_data[row1Id] };
	m_data[row1Id] = m_data[row2Id];
	m_data[row2Id] = temp;
}

template<typename T>
void Matrix<T>::changeCols(const size_t col1Id, const size_t col2Id)
{
	//If dimension is wrong throw exception
	if (col1Id >= m_cols || col2Id >= m_cols)
		throw std::out_of_range("Wrong dimensions");

	//If they are same columns don't change them
	if (col1Id == col2Id)
		return;
	
	//Change columns
	for (size_t i{ 0 }; i < m_rows; ++i)
	{
		T temp{ m_data[i][col1Id] };
		m_data[i][col1Id] = m_data[i][col2Id];
		m_data[i][col2Id] = temp;
	}
}

template<typename T>
Matrix<T> Matrix<T>::getTransposed() const
{
	//Create transposed matrix and fill it
	Matrix<T> res{ m_cols, m_rows };
	for (size_t i{ 0 }; i < m_rows; ++i)
		for (size_t j{ 0 }; j < m_cols; ++j)
			res.m_data[i][j] = m_data[j][i];

	return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator-() const
{
	//Copy matrix with change sign of all elements
	Matrix<T> res = *this;
	for (auto &row : res.m_data)
		for (auto &el : row)
			el = -el;

	return res;
}

template<typename T>
Matrix<T> operator+(const Matrix<T>& mat1, const Matrix<T>& mat2)
{
	//If dimentions not equal throw exctprion
	if (mat1.m_rows != mat2.m_rows || mat1.m_cols != mat2.m_cols)
		throw std::logic_error("Dimentions of matrices must be equal");

	//Copy first matrix and add to similar first matrix elements elements of second matrix
	Matrix<T> res{ mat1 };
	for (size_t i{ 0 }; i < res.m_rows; ++i)
		for (size_t j{ 0 }; j < res.m_cols; ++j)
			res.m_data[i][j] += mat2[i][j];

	return res;
}

template<typename T>
Matrix<T> operator*(const Matrix<T>& mat, const T &k)
{
	Matrix<T> res{ mat };
	//Multiplying all elements of matrix to constant value
	for (auto &row : res.m_data)
		for (auto &el : row)
			el *= k;

	return res;
}

template<typename T>
inline Matrix<T> operator*(const Matrix<T>& mat1, const Matrix<T>& mat2)
{
	//If dimentions not equal throw exctprion
	if (mat1.m_cols != mat2.m_rows)
		throw std::logic_error("Number of columns in left matrix must be equal to number of rows in right matrix");

	
	Matrix<T> res{ mat1.m_rows, mat2.m_cols };
	//Multiplying every row from left matrix to every column from right matrix
	for (size_t i{ 0 }; i < res.m_rows; ++i)
		for (size_t j{ 0 }; j < res.m_cols; ++j)
			for (size_t k{ 0 }; k < mat1.m_cols; ++k)
				res.m_data[i][j] += mat1.m_data[i][k] * mat2.m_data[k][j];

	return res;
}

template<typename T>
SqrMatrix<T>::SqrMatrix(const Matrix<T> &mat) 
	: Matrix<T>(mat)
{
	//If dimension is wrong throw exception
	if (this->m_rows != this->m_cols)
		throw std::logic_error("Wrong dimensions");
}

template<typename T>
SqrMatrix<T>::SqrMatrix(const std::initializer_list<std::initializer_list<T>> &list)
	: Matrix<T>(list)
{
	//If dimension is wrong throw exception
	if (this->m_rows != this->m_cols)
		throw std::logic_error("Wrong dimensions");
}

template<typename T>
Matrix<T>& SqrMatrix<T>::operator=(const Matrix<T> &mat)
{
	this->Matrix<T>::operator=(mat);

	//If dimension is wrong throw exception
	if (this->m_rows != this->m_cols)
		throw std::logic_error("Wrong dimensions");

	return *this;
}

template<typename T>
T SqrMatrix<T>::determinant() const
{
	if (this->m_cols == 1)
		return this->m_data[0][0];

	T res = T(0);

	//Decompose on the first column
	for (size_t k{ 0 }; k < this->m_rows; ++k)
	{
		if (this->m_data[k][0] == T(0))
			continue;

		SqrMatrix<T> minor{ this->m_rows - 1 };
		for (size_t i{ 0 }; i < this->m_rows; ++i)
			for (size_t j{ 1 }; j < this->m_cols; ++j)
			{
				if (i == k)
					continue;
				else if (i < k)
					minor.m_data[i][j - 1] = this->m_data[i][j];
				else if (i > k)
					minor.m_data[i - 1][j - 1] = this->m_data[i][j];
			}
		if (k % 2 == 0)
			res += this->m_data[k][0] * minor.determinant();
		else
			res -= this->m_data[k][0] * minor.determinant();
	}

	return res;
}

template<typename T>
SqrMatrix<T> SqrMatrix<T>::getInverse() const
{
	//Check if determinant equal zero then inverse matrix don't exist.
	T det = this->determinant();
	if (det == T(0))
		throw std::logic_error("Inverse matrix don't exist");

	//Create matrix of minors
	SqrMatrix<T> minorMatrix{ this->m_cols };

	//Get minor for all elements
	for (size_t minorRow{ 0 }; minorRow < this->m_rows; ++minorRow)
		for (size_t minorCol{ 0 }; minorCol < this->m_cols; ++minorCol)
		{
			//fill minor
			SqrMatrix<T> minor{ this->m_rows - 1 };
			for (size_t i{ 0 }; i < this->m_rows; ++i)
				for (size_t j{ 0 }; j < this->m_cols; ++j)
				{
					if (i == minorRow || j == minorCol)
						continue;
					else if (i < minorRow && j < minorCol)
						minor[i][j] = this->m_data[i][j];
					else if (i < minorRow && j > minorCol)
						minor[i][j - 1] = this->m_data[i][j];
					else if (i > minorRow && j < minorCol)
						minor[i - 1][j] = this->m_data[i][j];
					else if (i > minorRow && j > minorCol)
						minor[i - 1][j - 1] = this->m_data[i][j];
				}

			//Put minor to matrix of minors
			//Change sign of elements which have odd sum of indexes
			if ((minorRow + minorCol) % 2 == 0)
				minorMatrix[minorRow][minorCol] = minor.determinant();
			else 
				minorMatrix[minorRow][minorCol] = -minor.determinant();
		}

	//return Inverse matrix
	return 1 / det * minorMatrix.getTransposed();
}

