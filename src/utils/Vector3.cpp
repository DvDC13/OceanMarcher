#include "Vector3.h"

namespace Utils
{
    Vector3::Vector3()
        : m_x(0.0), m_y(0.0), m_z(0.0)
    {}

    Vector3::Vector3(double x, double y, double z)
        : m_x(x), m_y(y), m_z(z)
    {}

    Vector3 Vector3::operator-() const
    {
        return Vector3(-m_x, -m_y, -m_z);
    }

    Vector3& Vector3::operator+=(const Vector3& other)
    {
        m_x += other.m_x;
        m_y += other.m_y;
        m_z += other.m_z;
        return *this;
    }

    Vector3 Vector3::operator+(const Vector3& other) const
    {
        return Vector3(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
    }

    Vector3 Vector3::operator-(const Vector3& other) const
    {
        return Vector3(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
    }

    Vector3 Vector3::operator*(double scalar) const
    {
        return Vector3(m_x * scalar, m_y * scalar, m_z * scalar);
    }

    Vector3 Vector3::operator/(double scalar) const
    {
        return Vector3(m_x / scalar, m_y / scalar, m_z / scalar);
    }
} // namespace Utils