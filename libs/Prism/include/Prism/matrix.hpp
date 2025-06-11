#ifndef PRISM_MATRIX_HPP_
#define PRISM_MATRIX_HPP_

#include "prism_export.h"

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <vector>

namespace Prism {

template <typename T> class PRISM_EXPORT Matrix {
  public:
    /**
     * @brief Default constructor for matrix. If no arguments are given, constructs a 3x3 matrix
     * with all entries 0
     */
    Matrix() : rows_(3), cols_(3), data_(3, std::vector<T>(3, 0)){};

    /**
     * @brief Constructs a Matrix with given dimensions and initializes all elements to zero.
     * @param rows The number of rows in the matrix.
     * @param cols The number of columns in the matrix.
     */
    Matrix(size_t rows, size_t cols)
        : rows_(rows), cols_(cols), data_(rows, std::vector<T>(cols, 0)) {
        if (rows == 0 || cols == 0) {
            throw std::invalid_argument("Matrix dimensions must be greater than zero.");
        }
    };

    /**
     * @brief Constructs a Matrix from an initializer list of initializer lists.
     * @param data An initializer list containing rows of the matrix.
     */
    Matrix(std::initializer_list<std::initializer_list<T>> data);

    /**
     * @brief Copy constructor for Matrix.
     * @param m The matrix to copy from.
     */
    Matrix(const Matrix<T>& m) : rows_(m.rows_), cols_(m.cols_), data_(m.data_) {
    }

    /**
     * @brief Represents a row in the matrix.
     * This class provides access to the elements of a specific row in the matrix.
     */
    class MatrixRow {
      private:
        /**
         * @brief A row in the matrix represented as a vector.
         * This class provides access to the elements of a specific row.
         */
        std::vector<T>& m_row_vector;

      public:
        /**
         * @brief Constructs a MatrixRow from a vector.
         * @param row_vec A reference to the vector representing the row.
         */
        MatrixRow(std::vector<T>& row_vec) : m_row_vector(row_vec) {
        }

        /**
         * @brief Accesses an element in the row.
         * @param col The column index of the element to access.
         * @return A reference to the element at the specified column.
         * @throws std::out_of_range if the column index is out of bounds.
         */
        T& operator[](int col) {
            return m_row_vector.at(col);
        }
    };

    /**
     * @brief Represents a constant row in the matrix.
     * This class provides read-only access to the elements of a specific row in the matrix.
     */
    class ConstMatrixRow {
      private:
        /**
         * @brief A constant row in the matrix represented as a vector.
         * This class provides read-only access to the elements of a specific row.
         */
        const std::vector<T>& m_row_vector;

      public:
        /**
         * @brief Constructs a ConstMatrixRow from a constant vector.
         * @param row_vec A reference to the constant vector representing the row.
         */
        ConstMatrixRow(const std::vector<T>& row_vec) : m_row_vector(row_vec) {
        }

        /**
         * @brief Accesses an element in the row.
         * @param col The column index of the element to access.
         * @return A const reference to the element at the specified column.
         * @throws std::out_of_range if the column index is out of bounds.
         */
        const T& operator[](int col) const {
            return m_row_vector.at(col);
        }
    };

    /**
     * @brief Gets the number of rows in the matrix.
     * @return The number of rows.
     */
    size_t getRows() const {
        return rows_;
    }

    /**
     * @brief Gets the number of columns in the matrix.
     * @return The number of columns.
     */
    size_t getCols() const {
        return cols_;
    }

    /**
     * @brief Checks if this matrix is equal to another matrix.
     * @param m The matrix to compare with.
     * @return True if both matrices have the same dimensions and all elements are equal, false
     * otherwise.
     */
    bool operator==(const Matrix<T>& m) const;

    /**
     * @brief Checks if this matrix is not equal to another matrix.
     * @param m The matrix to compare with.
     * @return True if the matrices differ in dimensions or any element, false otherwise.
     */
    bool operator!=(const Matrix<T>& m) const;

    /**
     * @brief Assignment operator.
     * @param m The matrix to assign from.
     * @return Reference to this matrix.
     */
    Matrix<T>& operator=(const Matrix<T>& m);

    /**
     * @brief Multiplies this matrix by another matrix.
     * @param m The matrix to multiply with.
     * @return A new matrix that is the result of the multiplication.
     * @throws std::invalid_argument if the number of columns in this matrix does not match the
     * number of rows in the other matrix.
     */
    Matrix<T> operator*(const Matrix<T>& m) const;

    /**
     * @brief Multiplies this matrix by a scalar.
     * @param scalar The scalar value to multiply by.
     * @return A new matrix that is the result of the multiplication.
     */
    Matrix<T> operator*(const T& scalar) const;

    /**
     * @brief Multiplies this matrix by another matrix in place.
     * @param m The matrix to multiply with.
     * @return Reference to this matrix after multiplication.
     * @throws std::invalid_argument if the number of columns in this matrix does not match the
     * number of rows in the other matrix.
     */
    Matrix<T>& operator*=(const Matrix<T>& m);

    /**
     * @brief Multiplies this matrix by a scalar in place.
     * @param scalar The scalar value to multiply by.
     * @return Reference to this matrix after multiplication.
     */
    Matrix<T>& operator*=(const T& scalar);

    /**
     * @brief Accesses a row of the matrix.
     * @param i The index of the row to access.
     * @return A reference to the vector representing the row.
     * @throws std::out_of_range if the index is out of bounds.
     */
    MatrixRow operator[](size_t i) {
        if (i >= rows_)
            throw std::out_of_range("Row index out of bounds.");
        return MatrixRow(data_[i]);
    }

    /**
     * @brief Accesses a row of the matrix (const version).
     * @param i The index of the row to access.
     * @return A const reference to the vector representing the row.
     * @throws std::out_of_range if the index is out of bounds.
     */
    ConstMatrixRow operator[](size_t i) const {
        if (i >= rows_)
            throw std::out_of_range("Row index out of bounds.");
        return ConstMatrixRow(data_[i]);
    }

  private:
    size_t rows_;                      ///< Number of rows in the matrix
    size_t cols_;                      ///< Number of columns in the matrix
    std::vector<std::vector<T>> data_; ///< Matrix data
};

template <typename T> Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> data) {
    rows_ = data.size();

    if (rows_ == 0) {
        throw std::invalid_argument("Matrix cannot be initialized with an empty initializer list.");
    }

    cols_ = data.begin()->size();
    for (const auto& row : data) {
        if (row.size() != cols_) {
            throw std::invalid_argument(
                "All rows in the initializer list must have the same number of columns.");
        }
    }

    data_ = std::vector<std::vector<T>>(rows_, std::vector<T>(cols_));
    int i = 0;
    for (const auto& row : data) {
        int j = 0;
        for (const auto& val : row) {
            data_[i][j] = val;
            ++j;
        }
        ++i;
    }
}

template <typename T> bool Matrix<T>::operator==(const Matrix<T>& m) const {
    if (rows_ != m.rows_ || cols_ != m.cols_) {
        return false;
    }
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            if (data_[i][j] != m.data_[i][j]) {
                return false;
            }
        }
    }
    return true;
}

template <typename T> bool Matrix<T>::operator!=(const Matrix<T>& m) const {
    return !(*this == m);
}

template <typename T> Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m) {
    rows_ = m.rows_;
    cols_ = m.cols_;
    data_ = m.data_;

    return *this;
}

template <typename T> Matrix<T> Matrix<T>::operator*(const Matrix<T>& m) const {
    if (cols_ != m.rows_) {
        throw std::invalid_argument("Number of columns in the first matrix must match number of "
                                    "rows in the second matrix.");
    }

    Matrix<T> result(rows_, m.cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < m.cols_; ++j) {
            for (size_t k = 0; k < cols_; ++k) {
                result.data_[i][j] += data_[i][k] * m.data_[k][j];
            }
        }
    }
    return result;
}

template <typename T> Matrix<T> Matrix<T>::operator*(const T& scalar) const {
    Matrix<T> result(*this);
    result *= scalar;
    return result;
}

template <typename T> Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& m) {
    return *this = *this * m;
}

template <typename T> Matrix<T>& Matrix<T>::operator*=(const T& scalar) {
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            data_[i][j] *= scalar;
        }
    }
    return *this;
}

} // namespace Prism

#endif // PRISM_MATRIX_HPP_