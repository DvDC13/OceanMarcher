#pragma once

#include <iostream>
#include <cmath>
#include <algorithm>

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

        inline void setX(double x) { m_x = x; }
        inline void setY(double y) { m_y = y; }
        inline void setZ(double z) { m_z = z; }

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

    inline Vector3 operator*(const Vector3& a, const Vector3& b)
    {
        return Vector3(a.getX() * b.getX(), a.getY() * b.getY(), a.getZ() * b.getZ());
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

    inline Vector3 reflect(const Vector3& v, const Vector3& n)
    {
        return v - 2 * dot(v, n) * n;
    }

    inline static Vector3 random(double min, double max)
    {
        return Vector3(min + (max - min) * rand() / (RAND_MAX + 1.0),
                       min + (max - min) * rand() / (RAND_MAX + 1.0),
                       min + (max - min) * rand() / (RAND_MAX + 1.0));
    }

    inline static Vector3 randomInUnit()
    {
        while (true)
        {
            Vector3 p = random(-1, 1);
            if (lengthSquared(p) >= 1) continue;
            return p;
        }
    }

    inline bool nearZero(const Vector3& v)
    {
        const double s = 1e-8;
        return (std::abs(v.getX()) < s) && (std::abs(v.getY()) < s) && (std::abs(v.getZ()) < s);
    }

    // Check PAS BON
    inline double fresnel(const Vector3&v, const Vector3& n, double ior)
    {
        double cosi = std::clamp(dot(v, n), -1.0, 1.0);
        double etai = 1, etat = ior;
        
        if (cosi > 0)
        {
            std::swap(etai, etat);
        }

        double sint = etai / etat * std::sqrt(std::max(0.0, 1 - cosi * cosi));

        if (sint >= 1)
        {
            return 1;
        }
        else
        {
            double cost = std::sqrt(std::max(0.0, 1 - sint * sint));
            cosi = std::abs(cosi);
            double Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
            double Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
            return (Rs * Rs + Rp * Rp) / 2;
        }
    }

    using Point3 = Vector3;
    using Color3 = Vector3;
} // namespace Utils