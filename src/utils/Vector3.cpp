#include "Vector3.h"

namespace Utils
{
    Vector3::Vector3()
        : m_x(0.0), m_y(0.0), m_z(0.0)
    {}

    Vector3::Vector3(double x, double y, double z)
        : m_x(x), m_y(y), m_z(z)
    {}

    double Vector3::getX() const { return m_x; }
    double Vector3::getY() const { return m_y; }
    double Vector3::getZ() const { return m_z; }

    Vector3 Vector3::operator-() const
    {
        return Vector3(-m_x, -m_y, -m_z);
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

    double dot(const Vector3& a, const Vector3& b)
    {
        return a.getX() * b.getX() + a.getY() * b.getY() + a.getZ() * b.getZ();
    }

    Vector3 cross(const Vector3& a, const Vector3& b)
    {
        return Vector3(a.getY() * b.getZ() - a.getZ() * b.getY(),
                       a.getZ() * b.getX() - a.getX() * b.getZ(),
                       a.getX() * b.getY() - a.getY() * b.getX());
    }

    double lengthSquared(const Vector3& v) { return dot(v, v); }

    double length(const Vector3& v) { return std::sqrt(lengthSquared(v)); }

    Vector3 normalize(const Vector3& v) { return v / length(v); }

} // namespace Utils