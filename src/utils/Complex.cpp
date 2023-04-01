#include "Complex.h"

namespace Utils
{
    Complex::Complex()
        : m_real(0.0), m_imaginary(0.0)
    {}
    
    Complex::Complex(double real, double imaginary)
        : m_real(real), m_imaginary(imaginary)
    {}

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
} // namespace Utils
