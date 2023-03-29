#pragma once

#include <cmath>

namespace Utils
{
    class Vector2
    {
    public:
        Vector2();
        Vector2(double x, double y);

        inline double getX() const;
        inline double getY() const;

        inline Vector2 operator-() const;

        inline Vector2 operator+(const Vector2 &other) const;
        inline Vector2 operator-(const Vector2 &other) const;

        inline Vector2 operator*(double scalar) const;
        inline Vector2 operator/(double scalar) const;
    
    private:
        double m_x;
        double m_y;
    };

    inline Vector2 operator*(double scalar, const Vector2 &v);
    inline double dot(const Vector2 &a, const Vector2 &b);

    inline double lengthSquared(const Vector2 &v);
    inline double length(const Vector2 &v);
    inline Vector2 normalize(const Vector2 &v);
} // namespace Utils