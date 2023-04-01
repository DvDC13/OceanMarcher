#include "Gaussian.h"

namespace Utils
{
    double Randomdouble()
    {
        static std::uniform_real_distribution<double> distribution(0.0f, 1.0f);
        static std::mt19937 generator;
        return distribution(generator);
    }

    double GaussianNumber()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> d(0, 1);
        return d(gen);
    }
} // namespace Utils