#pragma once
#include <vector>

template<class T>
class Matrix
{
protected:
	size_t m_rows;
	size_t m_cols;
	std::vector <std::vector <T>> m_data;

public:
	explicit Matrix(const size_t rows = 0, const size_t cols = 0, const T &value = T(0));
	Matrix(const Matrix<T> &mat);
	Matrix(const std::initializer_list<std::initializer_list<T>> &list);
	Matrix<T>& operator=(const Matrix<T> &mat);
	virtual ~Matrix<T>() {}

	T& at(const size_t row, const size_t col);
	const T& at(const size_t row, const size_t col) const;
	std::vector<T>& operator[](const size_t row);
	const std::vector<T>& operator[](const size_t row) const;

	inline size_t maxSize() const { return std::numeric_limits<int>::max(); }
	inline size_t rows() const { return m_rows; }
	inline size_t cols() const { return m_cols; }
	std::vector<T> getRow(size_t rowId) const;
	std::vector<T> getCol(size_t colId) const;
	inline bool empty() const { return m_rows == 0 && m_cols == 0; }
	size_t rang() const;

	void resize(const size_t rows, const size_t cols, const T &value = 0);
	void clear();
	void insertRow(const size_t rowId, const std::vector<T> &row);
	void insertCol(const size_t colId, const std::vector<T> &col);
	void changeRows(const size_t row1Id, const size_t row2Id);
	void changeCols(const size_t col1Id, const size_t col2Id);

	inline void swap(Matrix<T> &mat) { Matrix<T> temp = *this; *this = mat; mat = temp; }
	inline friend void swap(Matrix<T> &mat1, Matrix<T> &mat2) { mat1.swap(mat2); }
	Matrix<T> getTransposed() const;

	Matrix<T> operator-() const;
	template<typename T>
	friend Matrix<T> operator+(const Matrix<T> &mat1, const Matrix<T> &mat2);
	template<typename T>
	inline friend Matrix<T> operator-(const Matrix<T> &mat1, const Matrix<T> &mat2) { return mat1 + (-mat2); }
	inline Matrix<T>& operator+= (const Matrix<T> &mat) { *this = *this + mat; return *this; }
	inline Matrix<T>& operator-= (const Matrix<T> &mat) { *this = *this + (-mat); return *this; }

	template<typename T>
	friend Matrix<T> operator*(const Matrix<T> &mat, const T &k);
	template<typename U>
	inline friend Matrix<U> operator*(const U &k, const Matrix<U> &mat) { return mat * k; }
	inline Matrix<T>& operator*=(const T &k) { *this = *this * k; return *this; }
	template<typename T>
	friend Matrix<T> operator*(const Matrix<T> &mat1, const Matrix<T> &mat2);
};

template<class T>
class SqrMatrix : public Matrix<T> {
public:
	explicit SqrMatrix(size_t size = 0, const T &value = T(0) ) : Matrix<T>(size, size, value) {}
	SqrMatrix(const Matrix<T> &mat);
	SqrMatrix(const std::initializer_list<std::initializer_list<T>> &list);
	Matrix<T>& operator=(const Matrix<T> &mat);
	virtual ~SqrMatrix() {}

	T determinant() const;
	SqrMatrix<T> getInverse() const;
};

#include "Matrix.inl"
