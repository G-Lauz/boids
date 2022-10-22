#include "matrix.h"


template<typename T, std::size_t COLS, std::size_t ROWS> 
boids::Matrix<T, COLS, ROWS>::Matrix()
{
    m_length = ROWS * COLS;
    m_matrix = new T[m_length]();
}


template<typename T, std::size_t COLS, std::size_t ROWS> 
boids::Matrix<T, COLS, ROWS>::Matrix(const T matrix[])
{
    m_length = ROWS * COLS;
    m_matrix = new T[m_length]();
    std::copy(matrix, matrix + m_length, m_matrix);
}


template<typename T, std::size_t COLS, std::size_t ROWS> 
boids::Matrix<T, COLS, ROWS>::Matrix(const Matrix &matrix)
{
    m_length = matrix.m_length;
    m_matrix = new T[m_length]();
    std::copy(matrix.m_matrix, matrix.m_matrix + m_length, m_matrix);
}


template<typename T, std::size_t COLS, std::size_t ROWS> 
boids::Matrix<T, COLS, ROWS>::~Matrix() {
    delete[] m_matrix;
}


template<typename T, std::size_t COLS, std::size_t ROWS> 
T& boids::Matrix<T, COLS, ROWS>::operator[](std::array<int, 2> idx)
{
    if (idx[0] > COLS-1 || idx[1] > ROWS-1) 
    {
        std::cout << "Index out of bounds." << std::endl;
        exit(1);
    }

    return m_matrix[idx[0] + idx[1] * COLS];
}


template<typename T, std::size_t COLS, std::size_t ROWS> 
const T& boids::Matrix<T, COLS, ROWS>::operator[](std::array<int, 2> idx) const
{
    if (idx[0] > COLS-1 || idx[1] > ROWS-1) 
    {
        std::cout << "Index out of bounds." << std::endl;
        exit(1);
    }

    return m_matrix[idx[0] + idx[1] * COLS];
}


template<typename T, std::size_t COLS, std::size_t ROWS> 
boids::Matrix<T, COLS, ROWS> boids::Matrix<T, COLS, ROWS>::operator+(const Matrix &b)
{
    return add(b);
}


template<typename T, std::size_t COLS, std::size_t ROWS> 
boids::Matrix<T, COLS, ROWS> boids::Matrix<T, COLS, ROWS>::operator-(const Matrix &b)
{
    return substract(b);
}


template<typename T, std::size_t COLS, std::size_t ROWS> 
boids::Matrix<T, COLS, ROWS> boids::Matrix<T, COLS, ROWS>::operator*(const T &b)
{
    return scalar_product(b);
}


template<typename T, std::size_t COLS, std::size_t ROWS> 
boids::Matrix<T, COLS, ROWS> boids::Matrix<T, COLS, ROWS>::add(const Matrix &b)
{
    if (ROWS != b.get_rows() && COLS != b.get_cols())
    {
        std::cout << "Can't add two matrix of different shape." << std::endl;
        exit(1);
    }

    Matrix<T, COLS, ROWS> result;
    for (int i =0; i < m_length; i++)
        result.m_matrix[i] = m_matrix[i] + b.m_matrix[i];

    return result;
}


template<typename T, std::size_t COLS, std::size_t ROWS> 
boids::Matrix<T, COLS, ROWS> boids::Matrix<T, COLS, ROWS>::substract(const Matrix &b)
{
    if (ROWS != b.get_rows() && COLS != b.get_cols())
    {
        std::cout << "Can't substract two matrix of different shape." << std::endl;
        exit(1);
    }

    Matrix<T, COLS, ROWS> result;
    for (int i =0; i < m_length; i++)
        result.m_matrix[i] = m_matrix[i] - b.m_matrix[i];

    return result;
}


template<typename T, std::size_t COLS, std::size_t ROWS> 
boids::Matrix<T, COLS, ROWS> boids::Matrix<T, COLS, ROWS>::scalar_product(const T &b)
{
    Matrix<T, COLS, ROWS> result;
    for (int i = 0; i < m_length; i++)
        result.m_matrix[i] = m_matrix[i] * b;
    return result;
}


template <typename T, std::size_t COLS, std::size_t ROWS>
boids::Matrix<T, COLS, ROWS> boids::Matrix<T, COLS, ROWS>::indentity()
{
    Matrix<T, COLS, ROWS> result;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            result[{j,i}] = i==j ? 1.f : 0.f;
    return result;
}


template <typename T, std::size_t COLS, std::size_t ROWS>
void boids::Matrix<T, COLS, ROWS>::translate(const Matrix<float, 1, 3> &vec) 
{
    for (int i = 0; i < vec.get_rows(); i++)
        (*this)[{COLS-1, i}] += vec[{0,i}];
}


template <typename T, std::size_t COLS, std::size_t ROWS>
T* boids::Matrix<T, COLS, ROWS>::value_ptr()
{
    return &m_matrix[0];
}


template<typename T, std::size_t COLS, std::size_t ROWS> 
void boids::Matrix<T, COLS, ROWS>::print() const
{
    std::string buf = "";

    buf.append("{ ");
    for (int i = 0; i < ROWS; i++)
    {
        if (i != 0)
            buf.append("  ");
        
        buf.append("{ ");
        for (int j = 0; j < COLS; j++)
        {
            buf.append(std::to_string((*this)[{j,i}]) + " ");
        }
        buf.append("}");

        constexpr size_t colsm1 = ROWS-1;
        if (i != colsm1)
            buf.append("\n");
    }
    buf.append(" }");

    std::cout << buf << std::endl;
}


template<typename T, std::size_t COLS, std::size_t ROWS> 
constexpr size_t boids::Matrix<T, COLS, ROWS>::get_rows() const
{
    return ROWS;
}


template<typename T, std::size_t COLS, std::size_t ROWS> 
constexpr size_t boids::Matrix<T, COLS, ROWS>::get_cols() const
{
    return COLS;
}


template class boids::Matrix<float, 2, 1>;
template class boids::Matrix<float, 3, 1>;
template class boids::Matrix<float, 4, 1>;

template class boids::Matrix<float, 1, 2>;
template class boids::Matrix<float, 1, 3>;
template class boids::Matrix<float, 1, 4>;

template class boids::Matrix<float, 2, 2>;
template class boids::Matrix<float, 3, 3>;
template class boids::Matrix<float, 4, 4>;

template class boids::Matrix<float, 2, 3>;
template class boids::Matrix<float, 3, 2>;

template class boids::Matrix<float, 3, 4>;
template class boids::Matrix<float, 4, 3>;
