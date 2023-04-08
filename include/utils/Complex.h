#pragma once

#include <cmath>

namespace Utils
{
    class Complex
    {
    public:
        Complex();
        Complex(double real, double imaginary);

        inline double getReal() const { return m_real; }
        inline double getImaginary() const { return m_imaginary; }

        Complex operator+(const Complex& other) const;
        Complex operator-(const Complex& other) const;
        Complex operator*(const Complex& other) const;

        Complex conjugate() const;

        Complex operator*(double scalar) const;
        Complex operator/(double scalar) const;

    private:
        double m_real;
        double m_imaginary;
    };

    inline Complex exp(const double theta)
    {
        return Complex(std::cos(theta), std::sin(theta));
    }

    inline Complex operator*(double scalar, const Complex& complex)
    {
        return complex * scalar;
    }
} // namespace Utils