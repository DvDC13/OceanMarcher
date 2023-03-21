#pragma once

#include <cmath>

namespace Utils
{
    class Vector3
    {
    public:
        Vector3();
        Vector3(double x, double y, double z);

        inline double getX() const;
        inline double getY() const;
        inline double getZ() const;

        inline Vector3 operator-() const;

        inline Vector3 operator+(const Vector3& other) const;
        inline Vector3 operator-(const Vector3& other) const;
        
        inline Vector3 operator*(double scalar) const;
        inline Vector3 operator/(double scalar) const;

    private:
        double m_x;
        double m_y;
        double m_z;
    };

    inline double dot(const Vector3& a, const Vector3& b);
    inline Vector3 cross(const Vector3& a, const Vector3& b);

    inline double lengthSquared(const Vector3& v);
    inline double length(const Vector3& v);
    inline Vector3 normalize(const Vector3& v);
} // namespace Utils