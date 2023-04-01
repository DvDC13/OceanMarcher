#pragma once

#include <cmath>

namespace Utils
{
    class Vector3
    {
    public:
        Vector3();
        Vector3(double x, double y, double z);

        inline double getX() const { return m_x; }
        inline double getY() const { return m_y; }
        inline double getZ() const { return m_z; }

        Vector3 operator-() const;

        Vector3& operator+=(const Vector3& other);

        Vector3 operator+(const Vector3& other) const;
        Vector3 operator-(const Vector3& other) const;
        
        Vector3 operator*(double scalar) const;
        Vector3 operator/(double scalar) const;

    private:
        double m_x;
        double m_y;
        double m_z;
    };

    inline Vector3 operator*(double scalar, const Vector3& v)
    {
        return v * scalar;
    }

    inline double dot(const Vector3& a, const Vector3& b)
    {
        return a.getX() * b.getX() + a.getY() * b.getY() + a.getZ() * b.getZ();
    }

    inline Vector3 cross(const Vector3& a, const Vector3& b)
    {
        return Vector3(a.getY() * b.getZ() - a.getZ() * b.getY(),
                       a.getZ() * b.getX() - a.getX() * b.getZ(),
                       a.getX() * b.getY() - a.getY() * b.getX());
    }

    inline double lengthSquared(const Vector3& v)
    {
        return dot(v, v);
    }

    inline double length(const Vector3& v)
    {
        return std::sqrt(lengthSquared(v));
    }

    inline Vector3 normalize(const Vector3& v)
    {
        return v / length(v);
    }

    using Point3 = Vector3;
    using Color3 = Vector3;
} // namespace Utils