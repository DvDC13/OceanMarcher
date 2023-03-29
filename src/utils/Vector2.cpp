#include "Vector2.h"

namespace Utils
{
    Vector2::Vector2()
        : m_x(0.0), m_y(0.0)
    {}

    Vector2::Vector2(double x, double y)
        : m_x(x), m_y(y)
    {}

    inline double Vector2::getX() const { return m_x; }

    inline double Vector2::getY() const { return m_y; }

    inline Vector2 Vector2::operator-() const
    {
        return Vector2(-m_x, -m_y);
    }

    inline Vector2 Vector2::operator+(const Vector2 &other) const
    {
        return Vector2(m_x + other.m_x, m_y + other.m_y);
    }

    inline Vector2 Vector2::operator-(const Vector2 &other) const
    {
        return Vector2(m_x - other.m_x, m_y - other.m_y);
    }

    inline Vector2 Vector2::operator*(double scalar) const
    {
        return Vector2(m_x * scalar, m_y * scalar);
    }

    inline Vector2 Vector2::operator/(double scalar) const
    {
        return Vector2(m_x / scalar, m_y / scalar);
    }

    inline Vector2 operator*(double scalar, const Vector2 &v)
    {
        return Vector2(v.getX() * scalar, v.getY() * scalar);
    }

    inline double dot(const Vector2 &a, const Vector2 &b)
    {
        return a.getX() * b.getX() + a.getY() * b.getY();
    }

    inline double lengthSquared(const Vector2 &v)
    {
        return dot(v, v);
    }

    inline double length(const Vector2 &v)
    {
        return std::sqrt(lengthSquared(v));
    }

    inline Vector2 normalize(const Vector2 &v)
    {
        return v / length(v);
    }
}