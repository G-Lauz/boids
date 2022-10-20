#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <iostream>
#include <vector>
#include <string>

typedef std::array<int, 2> shape2d;

namespace boids 
{
    class Matrix
    {
        private:
            size_t m_length;
            shape2d m_shape;
            std::vector<float> m_matrix;

        public:
            Matrix();
            Matrix(const shape2d& shape);
            Matrix(const float* matrix, const shape2d& shape);
            ~Matrix();

            float& operator[](shape2d idx);
            const float& operator[](shape2d idx) const;
            Matrix operator+(Matrix const &b);
            Matrix operator-(Matrix const &b);
            Matrix operator*(float const &b);
            Matrix operator*(const float* b);
            Matrix operator*(Matrix const &b);

            Matrix add(Matrix const &b);
            Matrix substract(Matrix const &b);
            Matrix scalar_product(float const &b);
            Matrix multiply(Matrix const &b);

            static Matrix indentity(const shape2d& shape);
            void translate(const float* vector);

            float* value_ptr();

            void print() const;
    };
}

#endif // MATRIX_H
