#include "Complex.h"

namespace Utils
{
    Complex::Complex(double real, double imaginary)
        : m_real(real), m_imaginary(imaginary)
    {}

    double Complex::getReal() const { return m_real; }
    double Complex::getImaginary() const { return m_imaginary; }

    Complex Complex::operator+(const Complex& other) const
    {
        return Complex(m_real + other.m_real, m_imaginary + other.m_imaginary);
    }

    Complex Complex::operator-(const Complex& other) const
    {
        return Complex(m_real - other.m_real, m_imaginary - other.m_imaginary);
    }

    Complex Complex::operator*(const Complex& other) const
    {
        return Complex(m_real * other.m_real - m_imaginary * other.m_imaginary,
                       m_real * other.m_imaginary + m_imaginary * other.m_real);
    }

    Complex Complex::conjugate() const
    {
        return Complex(m_real, -m_imaginary);
    }

    Complex Complex::operator*(double scalar) const
    {
        return Complex(m_real * scalar, m_imaginary * scalar);
    }

    Complex Complex::operator/(double scalar) const
    {
        return Complex(m_real / scalar, m_imaginary / scalar);
    }

    Complex exp(const double theta)
    {
        return Complex(std::cos(theta), std::sin(theta));
    }

} // namespace Utils
