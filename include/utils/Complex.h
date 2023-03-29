#pragma once

#include <cmath>

namespace Utils
{
    class Complex
    {
    public:
        Complex(double real, double imaginary);

        inline double getReal() const;
        inline double getImaginary() const;

        inline Complex operator+(const Complex& other) const;
        inline Complex operator-(const Complex& other) const;
        inline Complex operator*(const Complex& other) const;

        inline Complex conjugate() const;

        inline Complex operator*(double scalar) const;
        inline Complex operator/(double scalar) const;

    private:
        double m_real;
        double m_imaginary;
    };

    inline Complex exp(const double theta);
} // namespace Utils