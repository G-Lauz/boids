# include "matrix.h"


boids::Matrix::Matrix()
{
    m_shape = {4,4};
    m_length = m_shape[0] * m_shape[1];
    m_matrix = std::vector<float>(m_length, 0);
}

boids::Matrix::Matrix(const shape2d& shape):
    m_shape(shape)
{   
    m_length = m_shape[0] * m_shape[1];
    m_matrix = std::vector<float>(m_length, 0);
}

boids::Matrix::Matrix(const float* matrix, const shape2d& shape):
    m_shape(shape)
{
    // TODO check if matrix size match shape length
    m_length = m_shape[0] * m_shape[1];
    m_matrix = std::vector<float>(matrix, matrix + m_length);
}

boids::Matrix::~Matrix() {

}

float& boids::Matrix::operator[](shape2d idx)
{
    if (idx[0] > m_shape[0]-1 || idx[1] > m_shape[1]-1) 
    {
        std::cout << "Index out of bounds." << std::endl;
        exit(1);
    }

    return m_matrix[idx[1] + idx[0] * m_shape[1]];
}

const float& boids::Matrix::operator[](shape2d idx) const
{
    if (idx[0] > m_shape[0]-1 || idx[1] > m_shape[1]-1) 
    {
        std::cout << "Index out of bounds." << std::endl;
        exit(1);
    }

    return m_matrix[idx[1] + idx[0] * m_shape[1]];
}

boids::Matrix boids::Matrix::operator+(Matrix const &b)
{
    return add(b);
}

boids::Matrix boids::Matrix::operator-(Matrix const &b)
{
    return substract(b);
}

boids::Matrix boids::Matrix::operator*(float const &b)
{
    return scalar_product(b);
}

boids::Matrix boids::Matrix::operator*(const float* b)
{
    std::cout << sizeof(b)/sizeof(b[0]) << std::endl;
    Matrix mat(b, {1,4});
    mat.print();
    return multiply(mat);
}

boids::Matrix boids::Matrix::operator*(Matrix const &b)
{
    return multiply(b);
}

boids::Matrix boids::Matrix::add(Matrix const &b)
{
    if (m_shape != b.m_shape)
    {
        std::cout << "Can't add two matrix of different shape." << std::endl;
        exit(1);
    }

    Matrix result(m_shape);
    for (int i =0; i < m_length; i++)
        result.m_matrix[i] = m_matrix[i] + b.m_matrix[i];

    return result;
}

boids::Matrix boids::Matrix::substract(Matrix const &b)
{
    if (m_shape != b.m_shape)
    {
        std::cout << "Can't substract two matrix of different shape." << std::endl;
        exit(1);
    }

    Matrix result(m_shape);
    for (int i =0; i < m_length; i++)
        result.m_matrix[i] = m_matrix[i] - b.m_matrix[i];

    return result;
}

boids::Matrix boids::Matrix::scalar_product(float const &b)
{
    Matrix result(m_shape);
    for (int i = 0; i < m_length; i++)
        result.m_matrix[i] = m_matrix[i] * b;
    return result;
}

boids::Matrix boids::Matrix::multiply(Matrix const &b)
{
    std::cout << "(" << m_shape[0] << "," << m_shape[1] << ") * (" << b.m_shape[0] << "," << b.m_shape[1] << ")" << std::endl;
    this->print();
    b.print();


    if (m_shape[1] != b.m_shape[0])
    {
        std::cout << "Column of the left matrix doesn't match the rows of the right." << std::endl;
        exit(1);
    }

    Matrix result({m_shape[0], b.m_shape[1]});

    for (int i = 0; i < m_shape[0]; i++)
        for (int j = 0; j < b.m_shape[1]; j++)
            for (int k = 0; k < m_shape[1]; k++)
                result[{i,j}] += (*this)[{i,k}] * b[{k,j}];

    return result;
}

boids::Matrix boids::Matrix::indentity(const shape2d& shape)
{
    Matrix result(shape);
    for (int i = 0; i < shape[0]; i++)
        for (int j = 0; j < shape[1]; j++)
            result[{i,j}] = i==j ? 1.f : 0.f;
    return result;
}

void boids::Matrix::translate(const float* vector) 
{
    for (int i = 0; i < m_shape[1]-1; i++)
        (*this)[{i, m_shape[1]-1}] += vector[i];
}

float* boids::Matrix::value_ptr()
{
    return &m_matrix[0];
}

void boids::Matrix::print() const
{
    std::string buf = "";

    buf.append("{ ");
    for (int i = 0; i < m_shape[0]; i++)
    {
        if (i != 0)
            buf.append("  ");

        buf.append("{ ");
        for (int j = 0; j < m_shape[1]; j++)
        {
            buf.append(std::to_string((*this)[{i,j}]) + " ");
        }
        buf.append("}");

        if (i != m_shape[0]-1)
            buf.append("\n");
    }
    buf.append(" }");

    std::cout << buf << std::endl;
}
