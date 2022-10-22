#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <array>
#include <iostream>

namespace boids 
{
    template <typename T, std::size_t COLS, std::size_t ROWS>
    class Matrix
    {
        private:
            size_t m_length;
            T* m_matrix;

        public:
            Matrix();
            Matrix(const T matrix[]);
            Matrix(const Matrix &matrix);
            ~Matrix();

            T& operator[](std::array<int, 2> idx);
            const T& operator[](std::array<int, 2> idx) const;
            Matrix operator+(const Matrix &b);
            Matrix operator-(const Matrix &b);
            Matrix operator*(const T &b);

            // TODO move the definition in the .cpp
            template<std::size_t K>
            Matrix<T, K, ROWS> operator*(const Matrix<T, K, COLS> &b)
            {
                return multiply(b);
            }

            Matrix add(const Matrix &b);
            Matrix substract(const Matrix &b);
            Matrix scalar_product(const T &b);
            
            // TODO move the definition in the .cpp
            template<std::size_t K>
            Matrix<T, K, ROWS> multiply(const Matrix<T, K, COLS>  &b)
            {
                Matrix<T, K, ROWS> result;

                for (int i = 0; i < K; i++)
                    for (int j = 0; j < ROWS; j++)
                        for (int k = 0; k < COLS; k++)
                            result[{j,i}] += (*this)[{k,i}] * b[{j,k}];

                return result;
            }

            static Matrix indentity();
            void translate(const Matrix<float, 1, 3> &vec);

            T* value_ptr();

            void print() const;

            constexpr size_t get_rows() const;
            constexpr size_t get_cols() const;
    };
}

typedef boids::Matrix<float, 2, 1> vec2;
typedef boids::Matrix<float, 3, 1> vec3;
typedef boids::Matrix<float, 4, 1> vec4;

typedef boids::Matrix<float, 1, 2> vec2h;
typedef boids::Matrix<float, 1, 3> vec3h;
typedef boids::Matrix<float, 1, 4> vec4h;

typedef boids::Matrix<float, 2, 2> mat2;
typedef boids::Matrix<float, 3, 3> mat3;
typedef boids::Matrix<float, 4, 4> mat4;

typedef boids::Matrix<float, 2, 3> mat2x3;
typedef boids::Matrix<float, 3, 2> mat3x2;
typedef boids::Matrix<float, 3, 4> mat3x4;
typedef boids::Matrix<float, 4, 3> mat4x3;

#endif // MATRIX_H
