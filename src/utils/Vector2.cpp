#include "Vector2.h"

namespace Utils
{
    Vector2::Vector2()
        : m_x(0.0), m_y(0.0)
    {}

    Vector2::Vector2(double x, double y)
        : m_x(x), m_y(y)
    {}

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
}