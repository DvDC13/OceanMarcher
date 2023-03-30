#pragma once

#include <cmath>

namespace Utils
{
    class Vector2
    {
    public:
        Vector2();
        Vector2(double x, double y);

        inline double getX() const { return m_x; }
        inline double getY() const { return m_y; }

        Vector2 operator-() const;

        Vector2 operator+(const Vector2 &other) const;
        Vector2 operator-(const Vector2 &other) const;

        Vector2 operator*(double scalar) const;
        Vector2 operator/(double scalar) const;
    
    private:
        double m_x;
        double m_y;
    };

    inline Vector2 operator*(double scalar, const Vector2 &v)
    {
        return Vector2(scalar * v.getX(), scalar * v.getY());
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
} // namespace Utils