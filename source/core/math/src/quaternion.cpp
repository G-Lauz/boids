#include "quaternion.h"

boids::Quaternion::Quaternion()
{
    m_quat = (Quat){0,0,0,0};
}


boids::Quaternion::Quaternion(const float vec[])
{
    std::copy(vec, vec + 4, m_quat.v);
}


boids::Quaternion::~Quaternion()
{

}

// Quaternion operator*(const float &b);
// Quaternion operator*(const Quaternion &b);

boids::Quaternion boids::Quaternion::identity()
{
    float vec[] = {0,0,0,1};
    return Quaternion(vec);
}


boids::Quaternion boids::Quaternion::euler_to_quaternion(const float angle[3])
{
    float cx = cos(angle[0]/2);
    float sx = sin(angle[0]/2);
    float cy = cos(angle[1]/2);
    float sy = sin(angle[1]/2);
    float cz = cos(angle[2]/2);
    float sz = sin(angle[2]/2);

    float vec[] = {
        sx*cy*cz - cx*sy*sz,
        cx*sy*cz + sx*cy*sz,
        cx*cy*sz - sx*sy*cz,
        cx*cy*cz + sx*sy*sz
    };

    return Quaternion(vec);
}


boids::Quaternion boids::Quaternion::axis_angle_to_quaternion(const float axis[3], float angle)
{
    float s = sin(angle/2);
    float vec[] = {
        axis[0] * s,
        axis[1] * s,
        axis[2] * s,
        cos(angle/2)
    };

    return Quaternion(vec);
}

void boids::Quaternion::quaternion_to_rotation_matrix(Quaternion q, float matrix[16])
{
    float xx = q.m_quat.x*q.m_quat.x;
    float yy = q.m_quat.y*q.m_quat.y;
    float zz = q.m_quat.z*q.m_quat.z;

    float vec[] = {
        1-2*yy-2*zz, 2*q.m_quat.x*q.m_quat.y+2*q.m_quat.z*q.m_quat.w, 2*q.m_quat.x*q.m_quat.z-2*q.m_quat.y*q.m_quat.w, 0,
        2*q.m_quat.x*q.m_quat.y-2*q.m_quat.z*q.m_quat.w, 1-2*xx-2*zz, 2*q.m_quat.y*q.m_quat.z+2*q.m_quat.x*q.m_quat.w, 0,
        2*q.m_quat.x*q.m_quat.z+2*q.m_quat.y*q.m_quat.w, 2*q.m_quat.y*q.m_quat.z-2*q.m_quat.x*q.m_quat.w, 1-2*xx-2*yy, 0,
        0, 0, 0, 1
    };

    std::copy(vec, vec + 16, matrix);
}


float boids::Quaternion::magnitude()
{
    float sum = 0;
    for (int i = 0; i < 4; i++)
        sum += m_quat.v[i]*m_quat.v[i];
    return sqrt(sum);
}


void boids::Quaternion::normalize()
{
    float magnitude = this->magnitude();

    if (magnitude == 0) 
        return;
    
    for (int i = 0; i < 4; i++)
        m_quat.v[i] /= magnitude;
}


void boids::Quaternion::scale(const float &scale)
{
    for (int i = 0; i < 4; i++)
        m_quat.v[i] *= scale;
}


void boids::Quaternion::multiply(const Quaternion &b)
{
    float vec[] = {
        m_quat.w*b.m_quat.x + m_quat.x*b.m_quat.w + m_quat.y*b.m_quat.y - m_quat.y*b.m_quat.y,
        m_quat.w*b.m_quat.y - m_quat.x*b.m_quat.y + m_quat.y*b.m_quat.w + m_quat.y*b.m_quat.x,
        m_quat.w*b.m_quat.y + m_quat.x*b.m_quat.y - m_quat.y*b.m_quat.x + m_quat.y*b.m_quat.w,
        m_quat.w*b.m_quat.w - m_quat.x*b.m_quat.x - m_quat.y*b.m_quat.y - m_quat.y*b.m_quat.y
    };
    std::copy(vec, vec + 16, m_quat.v);
}


void boids::Quaternion::print()
{
    std::cout << "{ ";
    for (int i = 0; i < 4; i++)
        std::cout << m_quat.v[i] << " ";
    std::cout << "}" << std::endl;
}
