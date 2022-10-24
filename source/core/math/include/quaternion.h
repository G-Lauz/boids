#ifndef QUATERNION_H
#define QUATERNION_H

#include <algorithm>
#include <iostream>
#include <math.h>

namespace boids
{
    typedef union
    {
        float v[4];
        struct
        {
            float x;
            float y;
            float z;
            float w;
        };  
    } Quat;


    class Quaternion
    {
        private:
            Quat m_quat;
            
        public:
            Quaternion();
            Quaternion(const float vec[]);
            ~Quaternion();

            // Quaternion operator*(const float &b);
            // Quaternion operator*(const Quaternion &b);

            static Quaternion identity();
            static Quaternion euler_to_quaternion(const float angle[3]);
            static Quaternion axis_angle_to_quaternion(const float axis[3], float angle);
            static void quaternion_to_rotation_matrix(Quaternion q, float matrix[16]);

            float magnitude();
            void normalize();
            void scale(const float &scale);
            void multiply(const Quaternion &b);

            void print();
    };
}


#endif // QUATERNION_H
