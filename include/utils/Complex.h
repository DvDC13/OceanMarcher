#pragma once

#include <cmath>

namespace Utils
{
    class Complex
    {
    public:
        Complex();
        Complex(double real, double imaginary);

        double getReal() const;
        double getImaginary() const;

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
} // namespace Utils