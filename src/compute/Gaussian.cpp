#include "Gaussian.h"

namespace Utils
{
    double GaussianNumber()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> d(0, 1);
        return d(gen);
    }
} // namespace Utils